#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

void move_cursor_exp(int movement_factor);
// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(const char*, ...);

void monitor_write_hex(u32int);

void monitor_write_dec(u32int);

//void monitor_put_colored(char c, int bg, int fg);
//void monitor_write_colored(int bg, int fg, const char *c, ...)

#endif
