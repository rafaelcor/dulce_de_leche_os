#ifndef IDT_H
#define IDT_H

#include "common.h"

/* Defines an IDT entry */
typedef struct{
 u16int base_lo;
 u16int sel;        /* Our kernel segment goes here! */
 u8int always0;     /* This will ALWAYS be set to 0! */
 u8int flags;       /* Set using the above table! */
 u16int base_hi;
} __attribute__((packed)) idt_entry;

typedef struct{
 u16int limit;
 u32int base;
} __attribute__((packed)) idt_ptr;

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
idt_entry idt[256];
idt_ptr idtp;


/* This exists in 'start.asm', and is used to load our IDT */
void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(u8int, u32int, u16int, u8int);

/* Installs the IDT */
void idt_install();

#endif
