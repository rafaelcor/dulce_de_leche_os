#include "isr.h"

void isrs_install(){
 idt_set_gate(0, (u32int)isr0, 0x08, 0x8E);
 idt_set_gate(1, (u32int)isr1, 0x08, 0x8E);
 idt_set_gate(2, (u32int)isr2, 0x08, 0x8E);
 idt_set_gate(3, (u32int)isr3, 0x08, 0x8E);
 idt_set_gate(4, (u32int)isr4, 0x08, 0x8E);
 idt_set_gate(5, (u32int)isr5, 0x08, 0x8E);
 idt_set_gate(6, (u32int)isr6, 0x08, 0x8E);
 idt_set_gate(7, (u32int)isr7, 0x08, 0x8E);
 idt_set_gate(8, (u32int)isr8, 0x08, 0x8E);
 idt_set_gate(9, (u32int)isr9, 0x08, 0x8E);
 idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
 idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
 idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
 idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
 idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
 idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
 idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
 idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
 idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
 idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
 idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
 idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
 idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
 idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
 idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
 idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
 idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
 idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
 idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
 idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
 idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
 idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[32] = {
 "Division By Zero\n",
 "Debug\n",
 "Non Maskable Interrupt\n",
 "Breakpoint Exception\n",
 "Into Detected Overflow Exception\n",
 "Out of Bounds Exception\n",
 "Invalid Opcode Exception\n",
 "No Coprocessor Exception\n",
 "Double Fault Exception\n",
 "Coprocessor Segment Overrun Exception\n",
 "Bad TSS Exception\n",
 "Segment Not Present Exception\n",
 "Stack Fault Exception\n",
 "General Protection Fault Exception\n",
 "Page Fault Exception\n",
 "Unknown Interrupt Exception\n",
 "Coprocessor Fault Exception\n",
 "Alignment Check Exception\n",
 "Machine Check Exceptionv",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n",
 "Reserved\n"
};

void fault_handler(regs *r){
 if (r->int_no < 32){
  /* Display the description for the Exception that occurred.
  *  In this tutorial, we will simply halt the system using an
  *  infinite loop */
  monitor_write(exception_messages[r->int_no]);
  monitor_write(" Exception. System Halted!\n");
  for(;;);
 }
}
