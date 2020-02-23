#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "new_memLib.h"

#define GETPADDING(adress) ((size_t)(adress) % (8))
#define SHIFTS_FOR_WORD (3)
#define BITS_IN_BYTE (8)

typedef unsigned char byte;
typedef size_t word;

void *Memset(void *str, int c, size_t n)
{
	word *str_word_p = NULL;	   /* pointer to str as words 				  */
	byte *str_byte_p = (byte *)str;/* pointer to str as bytes  			  	  */
	word c_word = c & 0xff;		   /* mask to take only the first 8 bytes of c*/
	byte c_byte = c & 0xff;		   /* mask to take only the first 1 byte of c */
	size_t tail = 0;			   /* will take the tail of the word		  */
	int index = 0;
	int word_size = sizeof(word);

	/* duplicating the char to a word (3 steps using bit shifting): */
	for (index = SHIFTS_FOR_WORD; (1 << index) < (word_size * BITS_IN_BYTE);
		++index)
	{
		c_word = c_word | (c_word << (1 << index));
	}

	/* check the alignment - if the adress divides by the word_size and	 	  */
	/* n is not 0 - assign c_byte to each byte:							 	  */
	while (((word)str_byte_p % word_size) && n)
	{
		*str_byte_p = c_byte;
		--n;
		++str_byte_p;
		printf("single head char '%c' copied\n", *str_byte_p);
	}

	/* get the tail - by checking the bits of n and (word_size - 1): 		  */
	tail = n % word_size;
	
	/* assign the new word-size pointer to str: */
	str_word_p = (word *)str_byte_p;

	/* loop to duplicate the word-size c in str, using what left from n 	  */
	for (n >>= index - SHIFTS_FOR_WORD; n > 0; ++str_word_p, --n)
	{
		*str_word_p = c_word;
		printf("word of chars copied\n");
	}

	/* assign current str location to str_byte_pointer */
	str_byte_p = (byte *)str_word_p;
	
	/* add the chars of the tail */
	for (; tail != 0; --tail, str_byte_p++)
	{
		*str_byte_p = c_byte;
		printf("single tail char '%c' copied\n", *str_byte_p);
	}

	return (str);
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	word *dest_word_p = (word *)dest; /* pointer to dest as words */
	word *src_word_p = (word *)src;	  /* pointer to src as words  */
	byte *dest_byte_p = (byte *)dest; /* pointer to dest as bytes */
	byte *src_byte_p = (byte *)src;	  /* pointer to src as bytes  */
	
	size_t tail = 0; /* will take the tail of the word */
	int word_size = sizeof(word);

	/* check the alignment - if the adress of dest divides by the word_size   */
	/* and n is not 0 - assign chars of src to each byte: 					  */
	while (((word)dest_byte_p % word_size) && n)
	{
		*dest_byte_p = *src_byte_p;
		printf("single head char '%c' copied\n", *src_byte_p);
		--n;
		++dest_byte_p;
		++src_byte_p;
	}

	/* get the tail - by checking the bits of n and (word_size - 1) */
	tail = n % word_size;

	dest_word_p = (word *)dest_byte_p; /* make a new word-size pointer to dest*/
	src_word_p = (word *)src_byte_p; /* make a new word-size pointer to src   */

	/* main loop to duplicate the word-size chunks of dest to src,		*/ 
	/* using what left from n 											*/
	for (n /= word_size; n > 0; --n, ++src_word_p, ++dest_word_p)
	{
		*dest_word_p = *src_word_p;
		printf("word of src copied\n");
	}

	/* assign current strings location to the byte pointers */
	dest_byte_p = (byte *)dest_word_p;
	src_byte_p = (byte *)src_word_p;

	/* add the chars of the tail */
	for (;tail != 0; --tail, ++dest_byte_p, ++src_byte_p)
	{
		*dest_byte_p = *src_byte_p;
		printf("single tail char '%c' copied\n", *src_byte_p);
	}

	return (dest);
}

void *Memmove(void *dest, const void *src, size_t n)
{
	/* if the memory location of src is greater than dest - do memcpy */
	if ((word)dest < (word)src) 
	{
		return Memcpy(dest, src, n);
	}
	
	/* if the dest and src are aligned - try move in word chuncks*/
	if ((word)dest % sizeof(word) == 0 && (word)src % sizeof(word) == 0)
	{
		word *dest_word_p = (word *)dest; /* pointer to dest as words */
		word *src_word_p = (word *)src;	  /* pointer to src as words  */
		byte *dest_byte_p = (byte *)dest; /* pointer to dest as bytes */
		byte *src_byte_p = (byte *)src;	  /* pointer to src as bytes  */
		
		size_t tail = 0; /* will take the tail of the word */
		int word_size = sizeof(word);
 		
 		/* get the pointers to their last byte: */
 		dest_byte_p += (n - 1);
 		src_byte_p += (n - 1);
 		
 		/* get the tail - by checking the bits of n and (word_size - 1) */ 
 		tail = n % word_size;
 		
 		/* copy the chars of the tail */
		for (;tail != 0; --tail, --dest_byte_p, --src_byte_p)
		{
			*dest_byte_p = *src_byte_p;
			printf("single tail char '%c' copied\n", *src_byte_p);
		}
 		
 		/* loop to duplicate the word-size chunks of dest to src, */
		/* from the last to the first 							  */
		for (n /= word_size; n > 0; --n)
		{
			/* The reason we copy index n-1 and test n>0 is that  *
			* n is unsigned -- so testing n>=0 doesn't work.     */
			dest_word_p[n - 1] = src_word_p[n - 1];
			printf("word of src copied\n"); 
		}
	}
	else 
	{
		/* if they are not aligned - copy byte by byte from the end */
		byte *dest_byte_p = dest;
		const byte *src_byte_p = src;
 
		for (; n > 0; n--) 
		{
			dest_byte_p[n - 1] = src_byte_p[n - 1];
			printf("single char '%c' copied\n", dest_byte_p[n - 1]);
		}
	}
 
	return dest;
}
