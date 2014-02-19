#include "string.h"

char strcmp(const char *one, const char *two){
 u32int i = 0;
 while(one[i] == two[i]){
  if(!one[i]) return 1;
  i++;
 }
 return 0;
}

char charcmp(char *one, char *two){
 if (one == two){
	 return 0;
	 }
 else{
 return 1;}
}

u32int strlen(const char *string){
 u32int i = 0;
 while(string[i]){
  i++;
 }
 return i;
}
