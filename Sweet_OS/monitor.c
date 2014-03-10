#include "monitor.h"

u8int cursor_x = 0, cursor_y = 0;
u16int *video_memory = (void*) 0xB8000;

// Updates the hardware cursor.
static void move_cursor(){
 // The screen is 80 characters wide...
 u16int cursorLocation = cursor_y * 80 + cursor_x;
 outb(0x3D4, 14);      // Tell the VGA board we are setting the high cursor byte.
 outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
 outb(0x3D4, 15);      // Tell the VGA board we are setting the low cursor byte.
 outb(0x3D5, cursorLocation);  // Send the low cursor byte.
}
void move_cursor_exp(int movement_factor){
	u8int cursor_x = 0, cursor_y = 0;
    u16int *video_memory = (void*) 0xB8000;
    u16int cursorLocation = cursor_y * 80 + cursor_x + 7 + movement_factor;
    outb(0x3D4, 14);      // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);      // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);  // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll(){
 // Get a space character with the default colour attributes.
 u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
 u16int blank = 0x20 /* space */ | (attributeByte << 8);

 // Row 25 is the end, this means we need to scroll up
 if(cursor_y >= 25){
  // Move the current text chunk that makes up the screen
  // back in the buffer by a line
  int i;
  for (i = 0*80; i < 24*80; i++){
      video_memory[i] = video_memory[i+80];
  }

  // The last line should now be blank. Do this by writing
  // 80 spaces to it.
  for (i = 24*80; i < 25*80; i++){
      video_memory[i] = blank;
  }
  // The cursor should now be on the last line.
  cursor_y = 24;
 }
}

// Writes a single character out to the screen.
void monitor_put(char c){
 // The background colour is black (0), the foreground is white (15).
 u8int backColour = 0;
 u8int foreColour = 15;

 // The attribute byte is made up of two nibbles - the lower being the
 // foreground colour, and the upper the background colour.
 u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
 // The attribute byte is the top 8 bits of the word we have to send to the
 // VGA board.
 u16int attribute = attributeByte << 8;
 u16int *location;

 // Handle a backspace, by moving the cursor back one space
 if (c == 0x08 && cursor_x){
  cursor_x--;
 }

 // Handle a tab by increasing the cursor's X, but only to a point
 // where it is divisible by 8.
 else if (c == 0x09){
  cursor_x = (cursor_x+8) & ~(8-1);
 }

 // Handle carriage return
 else if (c == '\r'){
  cursor_x = 0;
 }

 // Handle newline by moving cursor back to left and increasing the row
 else if (c == '\n'){
  cursor_x = 0;
  cursor_y++;
 }
 // Handle any other printable character.
 else if(c >= ' '){
  location = video_memory + (cursor_y*80 + cursor_x);
  *location = c | attribute;
  cursor_x++;
 }

 // Check if we need to insert a new line because we have reached the end
 // of the screen.
 if (cursor_x >= 80){
  cursor_x = 0;
  cursor_y ++;
 }

 // Scroll the screen if needed.
 scroll();
 // Move the hardware cursor.
 move_cursor();
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear(){
 // Make an attribute byte for the default colours
 u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
 u16int blank = 0x20 /* space */ | (attributeByte << 8);

 int i;
 for (i = 0; i < 80*25; i++){
  video_memory[i] = blank;
 }

 // Move the hardware cursor back to the start.
 cursor_x = 0;
 cursor_y = 0;
 move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(const char *c, ...){
 void *pr;
 asm volatile ("movl %%ebp, %0" :: "g" (pr));
 pr += 12;
 u32int i = 0;
 while (c[i]){
  if(c[i] == '%'){
   i++;
   switch(c[i]){
    case '%':
     monitor_put('%');
     break;
    case 's':
     monitor_write((char*) *((u32int*) pr));
     pr += 4;
     break;
    case 'c':
     monitor_put((char) *((u32int*) pr));
     pr += 4;
     break;
    default:
     monitor_put('%');
     monitor_put(c[i]);
     break;
   }
   i++;
  }
  else{
   monitor_put(c[i++]);
  }
 }
}

void monitor_write_hex(u32int n){
 if(!n){
  monitor_put('0');
  return;
 }
 int i = 28;
 while(!((n >> i) & 0xF)){
  i -= 4;
 }
 while(i>=0){
  if(((n >> i) & 0xF)<10){
 monitor_put(((n >> i) & 0xF)+0x30);
  }
  else{
 monitor_put(((n >> i) & 0xF)+0x37);
  }
  i -= 4;
 }
}

void monitor_write_dec(u32int n){
 if(!n){
  monitor_put('0');
  return;
 }
 u32int i = 1000000000;
 while(!(n/i%10)){
  i /= 10;
 }
 while(i){
  monitor_put((n/i%10)+0x30);
  i /= 10;
 }
}

void monitor_put_colored(char c, int bg, int fg){
 // The background colour is black (0), the foreground is white (15).
 u8int backColour = bg;
 u8int foreColour = fg;

 // The attribute byte is made up of two nibbles - the lower being the
 // foreground colour, and the upper the background colour.
 u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
 // The attribute byte is the top 8 bits of the word we have to send to the
 // VGA board.
 u16int attribute = attributeByte << 8;
 u16int *location;

 // Handle a backspace, by moving the cursor back one space
 if (c == 0x08 && cursor_x){
  cursor_x--;
 }

 // Handle a tab by increasing the cursor's X, but only to a point
 // where it is divisible by 8.
 else if (c == 0x09){
  cursor_x = (cursor_x+8) & ~(8-1);
 }

 // Handle carriage return
 else if (c == '\r'){
  cursor_x = 0;
 }

 // Handle newline by moving cursor back to left and increasing the row
 else if (c == '\n'){
  cursor_x = 0;
  cursor_y++;
 }
 // Handle any other printable character.
 else if(c >= ' '){
  location = video_memory + (cursor_y*80 + cursor_x);
  *location = c | attribute;
  cursor_x++;
 }

 // Check if we need to insert a new line because we have reached the end
 // of the screen.
 if (cursor_x >= 80){
  cursor_x = 0;
  cursor_y ++;
 }

 // Scroll the screen if needed.
 scroll();
 // Move the hardware cursor.
 move_cursor();
}

/*void monitor_write_colored(int bg, int fg, const char *c, ...){
 void *pr;
 asm volatile ("movl %%ebp, %0" :: "g" (pr));
 pr += 12;
 u32int i = 0;
 while (c[i]){
  if(c[i] == '%'){
   i++;
   switch(c[i]){
    case '%':
     monitor_put_colored('%', bg, fg);
     break;
    case 's':
     monitor_write_colored((char*) *((u32int*) pr), bg, fg);
     pr += 4;
     break;
    case 'c':
     monitor_put_colored((char) *((u32int*) pr), bg, fg);
     pr += 4;
     break;
    default:
     monitor_put_colored('%', bg, fg);
     monitor_put_colored(c[i], bg, fg);
     break;
   }
   i++;
  }
  else{
   monitor_put(c[i++]);
  }
 }
}*/

