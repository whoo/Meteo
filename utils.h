#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
   
    
      
       
struct MemoryStruct { char *memory; size_t size; };
        
	 
char *strupr(char *s) { 
	unsigned c; 
	unsigned char *p = (unsigned char *)s; 
	while (c = *p) *p++ =(unsigned char)((int)c>130)?'E':toupper(c); 
	return s;
}

