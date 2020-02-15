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
		/* else - move to the nexy power of 2 */
		else
		{
			power2 = power2 << 1; 
		}
	}
	return (0);
}

/* ispower2 without a loop: */

/* function add one to an int by using bitwise operations only */
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


/* this function rotate the revNumber and the x number so that always the number
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

/*function withouut loop:
unsigned int reverseBitsB(unsigned int x)
{
	unsigned int revNumber = 0;
	
	
	return revNumber;
}	
 */
 
 	
/*function that check if both bits 2 and 6 are on: */	
int bothBits2And6(unsigned char character)
{
	int mask = 1;
	mask = mask << 1;
	if (mask & character)
	{
		mask = mask << 4;
		if (mask & character)
		{
			return (1); /* both bits are one */
		}
	}
	else
	{
		return (0);
	}
}

/* function that check if at least one ot the bits 2 and 6 are on: */
int orBits2And6(unsigned char character)
{
	int mask = 1;
	mask = mask << 1;
	switch (mask & character)
	{
		case (1): return (1);
		break;
	}
	
	mask = mask << 4;
	switch (mask & character)
	{
		{
		case (1): return (1);
		break;
		}
		{
		case (0): return (0);
		break;
		}
	}
}
	
int sawpBits3And5(unsigned char character)
{
	int mask = 1;
	mask = mask << 2; /* move to 3rd bit */
	if (mask & character) /* if on */
	{
		mask = mask << 2; /* move to 5th bit */
		if (mask & character) 	/* if on */
		{
			character = character & mask;
			mask = mask >> 2;
			character = character | mask;
		}
		else			/* is off */
		{
			character = character | mask;
			mask = mask >> 2;
			character = character & mask;
		}
	}
	else			/* is off */
	{
		mask = mask << 2; /* move to 5th bit */
		if (mask & character) 	/* if on */
		{
			character = character | mask;
			mask = mask >> 2;
			character = character & mask;
		}
		else			/* is off */
		{
			character = character & mask;
			mask = mask >> 2;
			character = character | mask;
		}
		
	}
	
	return character;
}
		
	
	
	
	
/* function that counts the number of set bits in an intiger */	
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
	
int setBitsNoLoop (int number)
{
	int counter = 0;
	
	/*Brian Kernighan's Algorithm */
	if(number) /* unset the first set bit */
	{
		number = number & (number - 1);
		++counter;
	}
	if
	
	return counter;
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
