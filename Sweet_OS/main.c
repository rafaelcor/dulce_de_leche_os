#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"

int main(){
 monitor_clear();
 monitor_write("Inicializando la IDT\n");
 idt_install();
 monitor_write("Inicializando las ISR\n");
 isrs_install();
 monitor_write("Inicializando las IRQ\n");
 irq_install();
 asm volatile ("sti");
 monitor_write("Inicializando el PIT\n");
 timer_install();
 
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  W to Sweet                     |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  We to Sweet                    |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  Wel to Sweet                   |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  Welc to Sweet                  |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  Welco to Sweet                 |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  Welcom to Sweet                |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 timer_wait(500);
 monitor_clear();
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\t\b\b\t\t\b|  Welcome to Sweet               |\n");
 monitor_write("\t\b\b\t\t---------------------------------\n");
 monitor_write("\n"); //You must not use simple comillas
 monitor_write("\n");
 monitor_write("\n");
 monitor_clear();
 timer_wait(500);

 monitor_write("Inicializando el teclado\n");
 keyboard_install();
 monitor_clear();

 monitor_write("%s>>>", "user");
 //monitor_write("%c", 'a');

 return 0;
}
