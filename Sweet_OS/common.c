#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value){
 asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port){
 u8int ret;
 asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
 return ret;
}

u16int inw(u16int port){
 u16int ret;
 asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
 return ret;
}

void memset(void *dir, u8int val, u32int times){
 u32int i = 0;
 while(i<times){
  ((u8int*) dir)[i] = val;
  i++;
 }
}
