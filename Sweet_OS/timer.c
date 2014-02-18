#include "timer.h"

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;

void timer_phase(int hz){
 int divisor = 1193180/hz;       /* Calculate our divisor */
 outb(0x43, 0x36);             /* Set our command byte 0x36 */
 outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
 outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void timer_handler(regs *r){
 /* Increment our 'tick count' */
 timer_ticks++;

 /*if (timer_ticks % TICKS == 0){
  monitor_write("Ha pasado un segundo\n");
 }*/
}

void timer_install(){
 timer_phase(TICKS);
 /* Installs 'timer_handler' to IRQ0 */
 irq_install_handler(0, timer_handler);
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks){
 u32int eticks;

 eticks = timer_ticks+ticks;
 while(timer_ticks < eticks);
}
