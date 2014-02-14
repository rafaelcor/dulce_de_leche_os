#include "kb.h"
int cont = 0;
char strtop[1000];//2 13
/* US KeyBoard */
unsigned char kbdus[128] = {
 0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
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
    0,	/* All other keys are undefined */
};

/* Handles the keyboard interrupt */
void keyboard_handler(regs *r){
 u8int scancode;
 char test[100];
 cont = 0;
 memset(strtop,'\0', 100);
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
  if (scancode == 28){
	  monitor_write("\n");
	  monitor_write("user>>>");
	  if (strtop == "clear"){
		   //monitor_write("\ntest\n");
		   monitor_clear();
		  }
	  monitor_write(strtop);
	  //strtop[] = "";
	  cont = 0;
	  //borrar todo su contenido
	  memset(strtop,'\0', 100);
  }
  else{
	  if ( (scancode >=2) && (scancode <= 13) || (scancode >= 16) && (scancode <= 27) || (scancode >= 30) && (scancode <= 41) || (scancode >= 44) && (scancode <= 53) || scancode == 55 || scancode == 74 || scancode == 78){
		  strtop[cont] = kbdus[scancode];
		  cont++;
	  }
  //monitor_write("\v");
  monitor_put(kbdus[scancode]);}
  
 }

void keyboard_install(){
 irq_install_handler(1, keyboard_handler);
}
