#ifndef COMMON_H
#define COMMON_H

typedef char s8int;
typedef short s16int;
typedef int s32int;
typedef unsigned char u8int;
typedef unsigned short u16int;
typedef unsigned int u32int;

typedef struct{
 u32int gs, fs, es, ds;      /* pushed the segs last */
 u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
 u32int int_no, err_code;    /* our 'push byte #' and ecodes do this */
 u32int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
} regs;

void outb(u16int, u8int);
u8int inb(u16int);
u16int inw(u16int);
void memset(void*, u8int, u32int);

#endif
