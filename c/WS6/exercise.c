/*****************************************************************************
This is the Functions c file. There are two more files: exercise.h (header
filr), exercise_tests.c (the main function = tests).

Written by Anat Wax on February 2020. Reviewed by Lior Cohen.
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"


long Pow2(unsigned int x, unsigned int y)
{
	long result = 0;
	
	result = 2 << (y-1);
	result *= x;

	return result;
}

/* ispower2 with loop: */
int IsPower2a(unsigned int n)
{
	unsigned int power2 = 2; /* 2^0 = 1 */
	
	if (1 == n)
	{
		return (1); /* n is a power of 2 */
	}
	
	while (power2 <= n)
	{
		if (power2 == n)
		{
			return (1); /* n is a power of 2 */
		}
		/* else - move to the next power of 2 */
		else
		{
			power2 = power2 << 1; 
		}
	}
	
	return (0);
	/* add that if n is zero, it sould also return 1 */
}


/* ispower2 without a loop: */
/* every number that is a power of 2 will always have only one bit on! */
int IsPower2b(unsigned int n)
{
	if((n & (n-1)) == 0) /* if there was onl one bit on */
	{
		return (1); /* number is a power of 2 */
	}
	else
	{
		return (0);
	}
}

/* 4. function add one to an int by using bitwise operations only */
int AddOne(int a)
{
	int mask = 1;
	
	/* run until encounter a '0', meaning */
	/* run	while a and mask are both 1   */
	while (a & mask)
	{
		a = a ^ mask;
		mask = mask << 1;
	}
	
	/* turn first 0 into a 1 */
	a = a ^ mask;	
	
	return a;
}

/* 5. function that recieves an array of unsigned ints */
/* and prints only he ints that have exactly 3 bits on */
void CountSet3Bits(unsigned int *array, int arraySize, unsigned int *result)
{
	int index = 0;
	int counter = 0;
	int j = 0;
	int cell = array[index];
	
	/* Brian Kernighan's Algorithm */
	for (index = 0; index < arraySize; ++index)
	{
		while(cell) /* unset the first set bit */
		{
			cell = cell & (cell - 1);
			++counter;
		}
		
		if(3 == counter)
		{
			result[j] = array[index];
			++j;
		}
		
		counter = 0;
		cell = array[index + 1];
	}
	
	return;
}	


/* 6. byte_mirror this function rotate the revNumber and the x  */ 
/* number so that always the number at possition 0 to x will be */
/* signed to the mirrored possition on revNumber. 				*/	
unsigned int ReverseBitsA(unsigned int number)
{
	unsigned int rev_number = 0;
	int counter = 0;
	while(number)
	{
		rev_number = rev_number << 1; /* rotating to next cell */
		
		if (number & 1)
		{
			rev_number =  rev_number | 1;
		}

		number = number >> 1;
		++counter;
	}
	
	while(counter < 8)
	{
		rev_number = rev_number << 1;
		++counter;
	}
	
	return rev_number;
}


/*** 7. byte_mirror NO loop */
/* function without loop: */
unsigned int ReverseBitsB(unsigned int x)
{
	/* it is static so it will go to the	*/
	/* stack ONLY when we call the function	for the first time	*/
	static int result[] = {0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10,
	0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x8, 0x88, 0x48, 0xc8, 0x28, 0xa8,
	0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x4, 0x84, 0x44,
	0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74,
	0xf4, 0xc, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c,
	0xdc, 0x3c, 0xbc, 0x7c, 0xfc, 0x2, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62,
	0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0xa, 0x8a, 0x4a,
	0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a,
	0xfa, 0x6, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56,
	0xd6, 0x36, 0xb6, 0x76, 0xf6, 0xe, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e,
	0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x1, 0x81, 0x41,
	0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71,
	0xf1, 0x9, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59,
	0xd9, 0x39, 0xb9, 0x79, 0xf9, 0x5, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65,
	0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0xd, 0x8d, 0x4d,
	0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d,
	0xfd, 0x3, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53,
	0xd3, 0x33, 0xb3, 0x73, 0xf3, 0xb, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b,
	0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x7, 0x87, 0x47,
	0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77,
	0xf7, 0xf, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f,
	0xdf, 0x3f, 0xbf, 0x7f, 0xff};

    return result[x];
}	

 	
/* 8. function that check if both bits 2 and 6 are on: */	
int BothBits2And6(unsigned char character)
{
	int mask = 1;
	
	return (character & (mask << 5) && (character & (mask << 1))) ? 1 : 0;
}


/* 9. function that check if at least one ot the bits 2 and 6 are on: */
int OrBits2And6(unsigned char character)
{
	int mask = 1;
	
	return (character & (mask << 5) || (character & (mask << 1))) ? 1 : 0;
}


 /*** 10. function that sweap between 3 and bit 5 and return the new number */	
int SawpBits3And5(unsigned char character)
{
	unsigned int bit3 = (character >> 3) & 1; /* get the value of bit 3 */
    unsigned int bit5 = (character >> 5) & 1; /* get the value of bit 5 */
    /* store their XOR value - 1 if they are different: */
    unsigned int xor_helper = (bit3 ^ bit5);

    /* ceating a mask: get the value back to its binary place */
    xor_helper = (xor_helper << 3) | (xor_helper << 5);

    /* XOR the helper with the original num to swap if needed */
    return (character ^ xor_helper);
}
	
		
/* 11. function that receives an unsigned int and returns the closest  */
/* (smaller) number that is divisible by 16 without a reminder 		   */	
unsigned int DivisbleBy16(unsigned int number)
{
	int one = 1;
	
	while((number % 16) != 0) /* if doesn't divide by 16 wihout remainder */
	{
		number = number ^ one;  /* shift the number --> */
		one = one << 1;			/* <-- one back */
	}
	
	return number;
}


/* 12. function that swaps 2 variables without using a third variable */
void Swap(int *x, int *y)
{
	*x = *x ^ *y;	
	*y = *y ^ *x;	
	*x = *x ^ *y;	
}
	
	
/* 13. function mall letters with _ between wothat counts the   */
/* number of set bits in an intiger 							*/	
int SetBits(int number)
{
	int counter = 0;
	
	/*Brian Kernighan's Algorithm */
	while(number) /* unset the first set bit */
	{
		number = number & (number - 1);
		++counter;
	}
	
	return counter;
}	


/*** 14. function count number of set bits  */ 
/*	 in an integer - without using a loop   */
int SetBitsNoLoop(int number)
{
	/* mask: 1010101010101010101010101010101 */
    number = (number & (0x55555555)) + ((number >> 1) & (0x55555555));

    /* mask: 110011001100110011001100110011 */
    number = (number & (0x33333333)) + ((number >> 2) & (0x33333333));

    /* mask: 1111000011110000111100001111 */
    number = (number & (0x0f0f0f0f)) + ((number >> 4) & (0x0f0f0f0f));

    /* mask: 111111110000000011111111 */
    number = (number & (0x00ff00ff)) + ((number >> 8) & (0x00ff00ff));

    /* mask: 1111111111111111 */
    number = (number & (0x0000ffff)) + ((number >> 16) & (0x0000ffff));

    return number;
}
	

/*** a program that recieves a float from to user, and print its bits 	  	 */
/* you must make a cast because you can't do bitwise operation on float.     */
/* this casting is to a pointer to int so after the casting yiu see the same */
/* float number, but call it as if it was an intiger						 */
int FloatInBits(float number) 
{
	int *p_number;
	int index = 0;
	
	p_number = (int *)&number;

	for(index = 31; index >= 0; --index)
	{
		printf("%d", BitReturn(*p_number,index));
	}

	return 0;
}


int BitReturn(int number, int index)   
{
	int buffer = number & (1 << index);

	if(buffer == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
	
	
	
