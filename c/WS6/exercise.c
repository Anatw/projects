/*****************************************************************************
This is the Functions c file. There are two more files: exercise.h (header
filr), exercise_tests.c (the main function = tests).

Written by Anat Wax on February 2020. Reviewed by Lior Cohen.
*****************************************************************************/
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>


long Pow2(unsigned int x, unsigned int y)
{
	long result = 0;
	
	result = 2 << (y-1);
	result *= x;

	return result;
}

/* ispower2 with loop: */
int ispower2a(unsigned int n)
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
}


/* ispower2 without a loop: */
/* every number that is a power of 2 will always have only one bit on! */
int ispower2b(unsigned int n)
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
int addOne(int a)
{
	int mask = 1;
	
	/* run until encounter a '0', meaning run while a and
	 mask are both 1 */
	while (a & mask)
	{
		a = a ^ mask;
		mask = mask << 1;
	}
	
	/* turn first 0 into a 1 */
	a = a ^ mask;	
	
	return a;
}

/* 5. function that recieves an array of unsigned ints and prints only he ints
that have exactly 3 bits on */
void countSet3Bits (unsigned int *array, int arraySize, unsigned int *result)
{
	int index = 0;
	int counter = 0;
	int j = 0;
	int cell = array[index];
	
	/*Brian Kernighan's Algorithm */
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


/* 6. byte_mirror this function rotate the revNumber and the x number so that always the number
at possition 0 to x will be signed to the mirrored possition on revNumber. */	
unsigned int reverseBitsA(unsigned int number)
{
	unsigned int revNumber = 0;
	int counter = 0;
	while(number)
	{
		revNumber = revNumber << 1; /* rotating to next cell */
		
		if (number & 1)
		{
			revNumber =  revNumber | 1;
		}

		number = number >> 1;
		++counter;
	}
	
	while(counter < 8)
	{
		revNumber = revNumber << 1;
		++counter;
	}
	
	return revNumber;
}


/*** 7. byte_mirror NO loop */
/* function without loop: */
unsigned int reverseBitsB(unsigned int x)
{
	unsigned int result[] = {0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80,
    208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 
    216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 
    212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 
    220, 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 
    210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 
    218, 58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 
    214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 
    222, 62, 190, 126, 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 
    209, 49, 177, 113, 241, 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 
    217, 57, 185, 121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 
    213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 
    221, 61, 189, 125, 253, 3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 
    211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 
    219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 
    215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 
    223, 63, 191, 127, 255};

    return result[x];
}	

 	
/* 8. function that check if both bits 2 and 6 are on: */	
int bothBits2And6(unsigned char character)
{
	int mask = 1;
	
	return (character & (mask << 5) && (character & (mask << 1))) ? 1 : 0;
}


/* 9. function that check if at least one ot the bits 2 and 6 are on: */
int orBits2And6(unsigned char character)
{
	int mask = 1;
	
	return (character & (mask << 5) || (character & (mask << 1))) ? 1 : 0;
}


 /*** 10. function thet sweap between 3 and bit 5 and return the new number */	
int sawpBits3And5(unsigned char character)
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
	
		
/* 11. function that receives an unsigned int and returns the closest (smaller)
number that is divisible by 16 without a reminder */	
unsigned int divisbleBy16 (unsigned int number)
{
	int one = 1;
	
	while((number % 16) != 0) /* if doesn't divide by 16 wihout remainder */
	{
		number = number ^ one;  /* shift the number --> */
		one = one << 1;			/* <-- one back */
	}
	
	return number;
}


/* 12. function that swaps 2 variables without using a thid variable */
/* int b = 7 = (0000-0111) ; 	int r = 20 = (0001-0100) ; */
void swap(int *x, int *y)
{
	*x = *x ^ *y;	/* 0001-0011 (19) */
	*y = *y ^ *x;	/* 0000-0111 (7) */
	*x = *x ^ *y;	/* 0001-0000 (16) */
}
	
	
/* 13. function that counts the number of set bits in an intiger */	
int setBits (int number)
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


/*** 14. function count number of set bits in an integer - without using a loop */
int setBitsNoLoop (int number)
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
	

/* a program that recieves a float from to user, and print its bits */
/* you must make a cast because you can't do bitwise operation on float.
    this casting is to a pointer to int so after the casting yiu see the same
    float number, but call it as if it was an intiger */
int floatInBits(float number) 
{
	int *f_number;
	int index = 0;
	f_number = (int *)&number;

	for (index = 31; index >= 0; --index)
	{
		printf("%d",bit_return(*f_number,index));
	}

	return 0;
}

int bit_return(int number, int index)   
{
	int buffer = number & (1 << index);

	if (buffer == 0) return 0;
	else return 1; 
}
	
	
	
