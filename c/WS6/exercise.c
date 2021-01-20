/*****************************************************************************
Different bitwise functions.

Written by Anat Wax, anatwax@gmail.com
February 2020
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
	unsigned int power2 = 2;
	
	if (1 == n)
	{
		return (1);
	}
	
	while (power2 <= n)
	{
		if (power2 == n)
		{
			return (1);
		}
		else
		{
			power2 = power2 << 1; 
		}
	}
	
	return (0);
}


/* Every number that is a power of 2 will always have only one bit on! */
int IsPower2b(unsigned int n)
{
	if((n & (n-1)) == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/* 4. Function add one to an int by using bitwise operations only */
int AddOne(int num)
{
	int mask = 1;
	
	while (num & mask)
	{
		num = num ^ mask;
		mask = mask << 1;
	}
	
	num = num ^ mask;	
	
	return num;
}

/* 5. Function that recieves an array of unsigned ints */
/* and prints only the ints that have exactly 3 bits on */
void CountSet3Bits(unsigned int *array, int arraySize, unsigned int *result)
{
	int index = 0;
	int counter = 0;
	int j = 0;
	int cell = array[index];
	
	/* Brian Kernighan's Algorithm */
	for (index = 0; index < arraySize; ++index)
	{
		while(cell)
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


/* 6. */	
unsigned int ReverseBitsA(unsigned int number)
{
	unsigned int rev_number = 0;
	int counter = 0;
	while(number)
	{
		rev_number <<= 1;
		
		if (number & 1)
		{
			rev_number |= 1;
		}

		number >>= 1;
		++counter;
	}

	rev_number <<= (8 - counter);	
	
	return rev_number;
}


/*** 7. byte_mirror NO loop */
/* function without loop: */
unsigned int ReverseBitsB(unsigned int x)
{
	/* Static function will be created on the stack only when the function will be called for the first time */
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

 	
/* 8. Check if both bits 2 and 6 are on: */	
int BothBits2And6(unsigned char character)
{
	int mask = 1;
	
	return ((character & (mask << 5)) && (character & (mask << 1))) ? 1 : 0;
}


/* 9. Check if at least one of the bits 2 and 6 are on: */
int OrBits2And6(unsigned char character)
{
	int mask = 1;
	
	return ((character & (mask << 5)) || (character & (mask << 1))) ? 1 : 0;
}


 /*** 10. Swap between the status of the 3rd and bit 5th bits */	
int SawpBits3And5(unsigned char character)
{
	unsigned int bit3 = (character >> 2) & 1;
    unsigned int bit5 = (character >> 4) & 1;
    /* store their XOR value - 1 if they are different: */
    unsigned int xor_helper = (bit3 ^ bit5);

    /* ceating a mask: get the value back to its binary place */
    xor_helper = (xor_helper << 2) | (xor_helper << 4);

    /* XOR the helper with the original num to swap if needed */
    return (character ^ xor_helper);
}
	
		
/* 11. Function that receives an unsigned int and returns the closest  */
/* (smaller) number that is divisible by 16 without a reminder 		   */	
unsigned int DivisbleBy16(unsigned int number)
{
	int one = 1;
	
	while((number % 16) != 0)
	{
		if (number & one)
		{
			number ^= one;
		}
		one <<= 1;
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
	
	
/* 13. */	
int CountBitsOn(int number)
{
	int counter = 0;
	
	/*Brian Kernighan's Algorithm */
	while(number)
	{
		number &= (number - 1);
		++counter;
	}
	
	return counter;
}	


/* 14. Count the number of set bits in an integer - without using a loop */
int CountBitsNoLoop(int number)
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
	

/* Function to print float as bits */
int FloatInBits(float number) 
{
	int *p_number = NULL;
	int index = 0;
	
	p_number = (int *)&number;

	for(index = 31; index >= 0; --index)
	{
		printf("%d", BitReturn(*p_number, index));
	}

	return 0;
}


int BitReturn(int number, int index)   
{
	int buffer = number & (1 << index);

	if (buffer == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
	