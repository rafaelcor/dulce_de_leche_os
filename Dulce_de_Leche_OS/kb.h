#ifndef KB_H
#define KB_H

#include "common.h"
#include "monitor.h"
#include "irq.h"

void keyboard_handler(regs*);
void keyboard_install();

#endif
