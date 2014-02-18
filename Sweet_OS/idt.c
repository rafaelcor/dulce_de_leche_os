#include "idt.h"

/* This exists in 'start.asm', and is used to load our IDT */
void idt_load(){
 asm volatile ("lidt idtp\n");
}

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags){
 idt[num].base_hi = base >> 16;
 idt[num].base_lo = base & 0xFFFF;
 idt[num].sel = sel;
 idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install(){
 /* Sets the special IDT pointer up, just like in 'gdt.c' */
 idtp.limit = (sizeof(idt_entry)*256)-1;
 idtp.base = (u32int) &idt;

 /* Clear out the entire IDT, initializing it to zeros */
 memset(&idt, 0, sizeof(idt_entry)*256);

 /* Add any new ISRs to the IDT here using idt_set_gate */

 /* Points the processor's internal register to the new IDT */
 idt_load();
}
