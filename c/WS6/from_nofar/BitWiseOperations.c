/******************************************************************************
							File: BitWiseOperations.c
 				implementation functions using bitwise operations					
							Written by: Noffar Gil
							   Review by:Anat Wax
							   
								Date: 16.02.2020

*******************************************************************************/

#include <stdio.h>

#include "BitWiseOperations.h"

/* return result of x*(2^y) */
long Pow2(unsigned int x, unsigned int y)
{
	unsigned int res_pwo_2 = 1;
	
	res_pwo_2 = (x << y);
	
	return (res_pwo_2);  
	
}	

int IsPowOfTwo(unsigned int num)
{
	if ((0 != num) && (0 == (num & (num - 1))))
	{
		return (1);
	}
	
	return (0);
}

int IsPowOfTwoWithLoop(unsigned int num)
{
	int counter = 0;
	
	while (0 != num)
	{
		num = (num & (num - 1));
		counter++;
	}
	if (counter == 1)
	{
		return (1);
	}
	
	return (0);
}

/* flip all bits after the rightmost 0 bit. and flip the rightmost 0 bit*/
int AddOneToInt(int num)
{
	int m = 1;
/* loop runs untill the first 0 bits */	
	while (num & m)
	{
		num = (num ^ m); /* flip all bits after the rightmost 0 bit.*/
		m <<= 1;
	}
	num = (num ^ m); /*flip the rightmost 0 bit*/
	return (num);
}

void printsIntsWithExactlyThreeBitsOn (unsigned int arr[], unsigned int len)
{
	unsigned int i;
	
	for (i = 0; i < len; ++i)
	{
		if (CountSetBits(arr[i]) == 3)
		printf("%u have 3 bits on\n", arr[i]);
	}
}

 /* loop through all bits of num, if a bit is set increment the counter */
unsigned int CountSetBits(unsigned int num)
{
	unsigned int count = 0;
	
	while (0 != num)
	{
		count += num & 1;
		num >>= 1;
	}
	return (count);
}

/*unsigned int ByteMirrorLoop(unsigned char num)
{
    unsigned char reverse_num = num;
    unsigned char count = sizeof(num) * 8 ;
    
    num >>= 1;
    while(num)
    {
    	reverse_num <<= 1;
    	reverse_num |= (num & 1);
    	num >>= 1;
    	count--;
    }
    reverse_num <<= count;
    return (reverse_num);
}
*/

int SawpTwoBits(unsigned int x, int first, int second)
{
	int bit1 = (x >> first) & 1;
	int bit2 = (x >> second) & 1;	
	int swap = 0;
	unsigned result = 0;
	
	swap = bit1 ^ bit2;				/* Doing XOR on both bits				*/

	swap = (swap << first) | (swap << second);	/* Putting the swaped bits 	*/
												/* back in their places		*/
	result = x ^ swap;

	return (result);    
}

unsigned int ByteMirrorLoop(unsigned char num)
{
	int bit1 = 0;
	int bit2 = 0;
	unsigned int mirror_num = num;

	for (bit1 = 0, bit2 = 7; bit2 > 3; ++bit1, --bit2)
	{
		mirror_num = SawpTwoBits(mirror_num, bit1, bit2);
	}

	return mirror_num;
}

unsigned int ByteMirrorNoLoop(unsigned int num)
{
    unsigned int result = 0;

    if (num & 1)
    {
        result |= 128;
    }
    if (num & 2)
    {
        result |= 64;
    }
    if (num & 4)
    {
        result |= 32;
    }
    if (num & 8)
    {
        result |= 16;
    }
    if (num & 16)
    {
        result |= 8;
    }
    if (num & 32)
    {
        result |= 4;
    }
    if (num & 64)
    {
        result |= 2;
    }
    if (num & 128)
    {
        result |= 1;
    }

    return result;
}

unsigned int IsTwoAndSixBitsAreOn(unsigned char ch)
{
	char sixth_on = 64; /* 01000000 */
	char second_on = 4; /* 00000100 */
	
	return (0 != ((ch & second_on) && (ch & sixth_on)));
}

unsigned int IsTwoOrSixBitsAreOn(unsigned char ch)
{
	char mask = 68; /* binary = 01000100, 2 and 6 are on */
	
	return (0 != (ch & mask));
}

unsigned char SwapBetweenThirdAndFifthBit(unsigned char ch) 
{ 
	unsigned int result = 0;
    /* Move third to rightmost side */
    unsigned int bit3 =  (ch >> 3) & 1; 
  
    /* Move fifth to rightmost side */
    unsigned int bit5 =  (ch >> 5) & 1; 
  
    /* XOR the two bits */
    unsigned int x = (bit3 ^ bit5); 
  
    /* Put the xor bit back to their original positions */
    x = (x << 3) | (x << 5); 
  
    /* XOR 'x' with the original char so that the 
       two sets are swapped */
    result = (ch ^ x); 
    
    return (result); 
}

unsigned int ClosetNumDivisibleBy16(unsigned int num)
{
	int i = 0;
	
	for (i = num; i > 0; --i)
	{
		if (1 == IsDivisibleBy16(i))
		{
			return (i);
		}
	}
	return (0); /*remove */
}

int IsDivisibleBy16(unsigned int num)
{
	if (0 == num || 16 == num)
	{
		return (1);
	}
	 
	return (((num >> 4) << 4) == num);
}

void SwapWithBitwise(int *pa, int *pb)
{
	if((pa == pb) || (0 == pa) || (0 == pb))
		return;
		
	*pa = *pa ^ *pb;
	*pb = *pa ^ *pb;
	*pa = *pa ^ *pb;	
}

unsigned int CountSetBitsNoLoop(unsigned int num)
{
    /* mask: 1010101010101010101010101010101 */
    num = (num & (0x55555555)) + ((num >> 1) & (0x55555555));

    /* mask: 110011001100110011001100110011 */
    num = (num & (0x33333333)) + ((num >> 2) & (0x33333333));

    /* mask: 1111000011110000111100001111 */
    num = (num & (0x0f0f0f0f)) + ((num >> 4) & (0x0f0f0f0f));

    /* mask: 111111110000000011111111 */
    num = (num & (0x00ff00ff)) + ((num >> 8) & (0x00ff00ff));

    /* mask: 1111111111111111 */
    num = (num & (0x0000ffff)) + ((num >> 16) & (0x0000ffff));

    return num;
}

void PrintFloatBits(float num)
{
    int i = 0;
    int four_counter = 1;
    int *float_pointer = (int *)&num;
    for (i = 31; i >= 0; i--, four_counter++)
    {
        int buf = *float_pointer & 1 << i;
        printf("%d", (buf != 0));
        if (four_counter == 4)
        {
            printf(" ");
            four_counter = 0;
        }
    }
    printf("\n");
}



















