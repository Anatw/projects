#include <stdio.h>		/* sizeof() */
#include <string.h>

#include "memLib.h"

#define sizeof(size_t) sizeT

/* this function cpy an unsigned char to the first n chars in the string */
void *Memset(void *str, int c, size_t n)
{
	char array[] = "$c$c$c$c$c$c$c$c";
	size_t *tempNum = (size_t)aray;
	size_t *tempStr = (size_t)str;
	int index = 0;
	int wordNum = (n / sizeT);
	
	for(indx = 0; index < wordNum; ++index)
	{
		*((size_t *)str) = *((size_t *)array);
		str += sizeT;
	}
	
	wordNum = (n % sizeT);
	for(indx = 0; index < wordNum; ++index)
	{
		*str = c;
		++str;
	}
}



/*
void *Memcpy(void *str1, const void *str2, size_ n)
void *Memmove)void *str1, const void *str2, size_t n)
*/
