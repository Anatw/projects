#include <stdio.h>		/* sizeof() */
#include <string.h>
#include <stdlib.h>		/* malloc() */

#include "memLib.h"

#define sizeof(size_t) WORD

/* this function cpy an unsigned char to the first n chars in the string */
void *Memset(void *str, int c, size_t n)
{
	char *str_byte_p = (char *)str; 
	char *array = (char *)malloc(WORD * (sizeof(size_t)));
	size_t *tempNum = (size_t *)array;
	size_t *tempStr = (size_t *)str;
	int index = 0;
	int wordNum = (n / WORD);
	
	/* creating an array of 8 bytes, containing c in all bytes */
	for(index = 0; index < WORD; ++index)
	{
		array[index] = c;
	}
	
	while(((int)array % 8) && n)
	{
		array[index] = c;
		++index;
		--n;
	}
		
	for(index = 0; index < wordNum; ++index)
	{
		*((size_t *)str) = *((size_t *)array);
		str_byte_p += WORD;
	}
	
	wordNum = (n % WORD);
	for(index = 0; index < wordNum; ++index)
	{
		*str_byte_p = c;
		++str_byte_p;
	}
}
/*
void *Memcpy(void *str1, const void *str2, size_ n)
void *Memmove)void *str1, const void *str2, size_t n)
*/

