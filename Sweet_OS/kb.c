#include "kb.h"
#include "string.h"

int cont = 0;
char strtop[1000];//2 13
int text_cursor_cont = 0;
int other_cont = 0;

unsigned char letras_minusculas[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x' , 'y', 'z'};
unsigned char letras_mayusculas[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X' , 'Y', 'Z'}; 
 

/* US KeyBoard */
unsigned char kbdus[128] = {
	0,
	0, //Escape 
	'1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */ //de 16
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */ //a 27
     0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
    0,	/* Alt */
	' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,
    0,
    0 /*Windows key*/
    ,0 
    , 0/*Right click key*/ 	
};

/* Handles the keyboard interrupt */
void keyboard_handler(regs *r){
 u8int scancode;
 //char test[100];
 //cont = 0;
 //memset(strtop,'\0', 100);
 /* Read from the keyboard's data buffer */
 scancode = inb(0x60);

 /* If the top bit of the byte we read from the keyboard is
 *  set, that means that a key has just been released */
 if (scancode & 0x80){
  /* You can use this one to see if the user released the
  *  shift, alt, or control keys... */
 }
 /* Here, a key was just pressed. Please note that if you
 *  hold a key down, you will get repeated key press
 *  interrupts. */
 else{
  if (scancode == 28){
   monitor_put('\n');
   if(strcmp(strtop, "clear")){
    //monitor_write("\ntest\n");
    monitor_clear();
   }
   else if (strtop[0] == 'e' && strtop[1] == 'c' && strtop[2] == 'h' && strtop[3] == 'o' && strtop[4] == ' '){
	   //if (strtop[5] == '-' && strtop[6] == 'c'){
		   //echo -vbgfg echo -v0015
		   //}
	   //else{
		   monitor_write("%s\n", &strtop[5]);
		  // }
    
   }
   else if(strcmp(strtop, "reboot")){
	   reboot();
	   }
   else{
	   if(strcmp(strtop, "") == 0){
	       monitor_write("Command not found\n");
	   }
   }
   monitor_write("user>>>");
   cont = 0;
   //borrar todo su contenido
   memset(strtop,'\0', 100);
  }
  /*else{
	  if ( (scancode > 1 )&& (scancode < 28) || 
	     ( (scancode > 29) && (scancode < 42))|| 
	     ((scancode > 43) && (scancode < 54))){
	      text_cursor_cont++;}
	  else if (kbdus[scancode] == '\b'){
			text_cursor_cont--;}
	  else if (scancode == 88){
	      monitor_clear(); 
      }
	  }*/
  else if ( (scancode == 42)){
	  //monitor_write("hello");
	  monitor_write("%c", upper_letra('f'));
	  /*if( (scancode > 15) && (scancode < 26) || (scancode > 30) && (scancode < 39) || (scancode < 43) && (scancode > 51)){
		  //strtop[cont] = upper_letra(kbdus[scancode]);
		  monitor_write("%c", upper_letra('f'));
		  }*/
      if(scancode == 2){
		  monitor_write("two");
		  }
	  }
  else if (kbdus[scancode] == '\b'){
   if(cont>0){
    strtop[cont--] = 0;
    monitor_write("\b \b");
   }
  }
  else if (scancode == 75){
	  other_cont -= 1;
	  move_cursor_exp(text_cursor_cont - other_cont);
	  }
  else{
   strtop[cont] = kbdus[scancode];
   cont++;
   monitor_put(kbdus[scancode]);
  }
 }
}

void keyboard_install(){
 memset(strtop,'\0', 100);
 irq_install_handler(1, keyboard_handler);
}

char upper_letra(char letra){
	int i;
    int message = 0;
	char toreturn;
	for (i=0; i<27;){
		if ( ("%c", letras_minusculas[i]) == letra){
			message = 1;
			toreturn = letras_mayusculas[i];
			}
		i++;
	}
	if (message == 1){
		return toreturn;
		}
	else{
		return '0';}
}
char lower_letra(char letra){
	int i;
	int message = 0;
	char toreturn;
	for (i=0; i<27;){
		if ( ("%c", letras_mayusculas[i]) == letra){
			message = 1;
			toreturn = letras_minusculas[i];
			}
		i++;
	}
	if (message == 1){
		return toreturn;
		}
	else{
		return '0';}
}
