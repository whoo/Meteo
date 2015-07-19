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

char convert(unsigned char c)
{
	if (0xbf<c && c<0x86) return 'A';
	if (0x87<c && c<0x8c) return 'E';
	if (0x8b<c && c<0x90) return 'I';
	if (0x91<c && c<0x97) return 'O';
	if (0x98<c && c<0x9d) return 'U';
	if (0x9f<c && c<0xa7) return 'a';
	if (0xa7<c && c<0xac) return 'e';
	if (0xac<c && c<0xb0) return 'i';
	if (0xb1<c && c<0xb7) return 'o';
	if (0xb8<c && c<0xbd) return 'u';
	if (0x87==c || c==0xa7) return 'c';
	return '.';
}

void push(void *str,char c)
{

	struct MemoryStruct *mem=(struct MemoryStruct *)str;
//	printf("%d ]\n",mem->size);
//	mem->memory=realloc( mem->memory, mem->size +1);
	mem->memory[mem->size]=toupper(c);
	mem->size++;
	mem->memory[mem->size]=0;
};


char *Supper(char *tb)
{
	struct MemoryStruct MyStr;
	MyStr.memory=malloc(strlen(tb));
	MyStr.size=0;

	for(int a=0;tb[a];a++)
	{
		unsigned char nbchar=1;
		if ((tb[a]&0xc2) == 0xc2) { 
			if ((tb[a]&0xe0) == 0xe0)  nbchar=3; 
			else nbchar=2;
		}


		switch (nbchar) {
			case 2: a+=1; 
				push((void*)&MyStr,convert(tb[a]));
//				printf("%s - %x\n",MyStr.memory,tb[a]); 
				break;

			case 3: a+=2; 
				push((void*)&MyStr,'\'');
//				printf("%s - %x\n",MyStr.memory,tb[a]);
				break;
			default: 

				push((void*)&MyStr,tb[a]);
//				printf("%s - %x\n",MyStr.memory,tb[a]);

		}
	}

	return MyStr.memory;

}
