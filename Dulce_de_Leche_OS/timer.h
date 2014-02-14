#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "monitor.h"
#define TICKS 18

void timer_phase(int);

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(regs*);

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install();

#endif
