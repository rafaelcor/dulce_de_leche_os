#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"

int main(){
 monitor_clear();
 monitor_write("...Dulce de Leche OS...\n");
 idt_install();
 isrs_install();
 irq_install();
 asm volatile ("sti");
 timer_install();
 keyboard_install();
 return 0;
}
