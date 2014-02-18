#include "string.h"

char strcmp(const char *one, const char *two){
 u32int i = 0;
 while(one[i] == two[i]){
  if(!one[i]) return 1;
  i++;
 }
 return 0;
}

u32int strlen(const char *string){
 u32int i = 0;
 while(string[i]){
  i++;
 }
 return i;
}
