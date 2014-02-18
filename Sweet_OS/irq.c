#include "irq.h"

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int irq, void (*handler)(regs*)){
 irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq){
 irq_routines[irq] = 0;
}

void irq_remap(){
 outb(0x20, 0x11);
 outb(0xA0, 0x11);
 outb(0x21, 0x20);
 outb(0xA1, 0x28);
 outb(0x21, 0x04);
 outb(0xA1, 0x02);
 outb(0x21, 0x01);
 outb(0xA1, 0x01);
 outb(0x21, 0x0);
 outb(0xA1, 0x0);
}

void irq_install(){
 irq_remap();
 idt_set_gate(32, (u32int)irq0, 0x08, 0x8E);
 idt_set_gate(33, (u32int)irq1, 0x08, 0x8E);
 idt_set_gate(34, (u32int)irq2, 0x08, 0x8E);
 idt_set_gate(35, (u32int)irq3, 0x08, 0x8E);
 idt_set_gate(36, (u32int)irq4, 0x08, 0x8E);
 idt_set_gate(37, (u32int)irq5, 0x08, 0x8E);
 idt_set_gate(38, (u32int)irq6, 0x08, 0x8E);
 idt_set_gate(39, (u32int)irq7, 0x08, 0x8E);
 idt_set_gate(40, (u32int)irq8, 0x08, 0x8E);
 idt_set_gate(41, (u32int)irq9, 0x08, 0x8E);
 idt_set_gate(42, (u32int)irq10, 0x08, 0x8E);
 idt_set_gate(43, (u32int)irq11, 0x08, 0x8E);
 idt_set_gate(44, (u32int)irq12, 0x08, 0x8E);
 idt_set_gate(45, (u32int)irq13, 0x08, 0x8E);
 idt_set_gate(46, (u32int)irq14, 0x08, 0x8E);
 idt_set_gate(47, (u32int)irq15, 0x08, 0x8E);
}

void irq_handler(regs *r){
 /* This is a blank function pointer */
 void (*handler)(regs *r);

 /* Find out if we have a custom handler to run for this
 *  IRQ, and then finally, run it */
 handler = irq_routines[r->int_no-32];

 if (handler){
  handler(r);
 }

 /* If the IDT entry that was invoked was greater than 40
 *  (meaning IRQ8 - 15), then we need to send an EOI to
 *  the slave controller */
 if (r->int_no >= 40){
  outb(0xA0, 0x20);
 }

 /* In either case, we need to send an EOI to the master
 *  interrupt controller too */
 outb(0x20, 0x20);
}
