/*******************************************************************************
					  	 Written by Anat Wax
						  February 24, 2020
						Reviewer: Amir Paz
*******************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <assert.h> /* assert() */

#include "bit_array.h"

#define TO_NUMBER (48) /* '0' in ASCII */
#define MASK_ALL_ON (0xff)

char *BitArrayToString(bit_array_t array, char *dest)
{
	unsigned int i = 0;
	array = BitArrayMirror(array);
	
	for(i = 0; i < ARRAY_LENGTH; ++i, array >>= 1)
	{
		dest[i] = ((char)(array & 1) + TO_NUMBER);
	}
	
	dest[i] = '\0';
	
	return (dest);
}


/******************************************************************************/
bit_array_t BitArrayMirror(bit_array_t array)
{
	bit_array_t reverse = array;
	
	static int rev_lut[] = {0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10,
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
	
	reverse = (bit_array_t)rev_lut[array & MASK_ALL_ON] << 56|
		 	  (bit_array_t)rev_lut[(array >> 8) & MASK_ALL_ON] << 48 |
		 	  (bit_array_t)rev_lut[(array >> 16) & MASK_ALL_ON] << 40 |
		 	  (bit_array_t)rev_lut[(array >> 24) & MASK_ALL_ON] << 32 |
		 	  (bit_array_t)rev_lut[(array >> 32) & MASK_ALL_ON] << 24 |
		 	  (bit_array_t)rev_lut[(array >> 40) & MASK_ALL_ON] << 16 |
		 	  (bit_array_t)rev_lut[(array >> 48) & MASK_ALL_ON] << 8 |
		 	  (bit_array_t)rev_lut[(array >> 56) & MASK_ALL_ON];
		
	return (reverse);
}

/******************************************************************************/
bit_array_t BitArraySetAll()
{
	return (~0);
}

/******************************************************************************/
bit_array_t BitArrayResetAll()
{
	return (0);
}

/******************************************************************************/
bit_array_t BitArraySetOn(bit_array_t array, unsigned int index)
{
	bit_array_t mask = 1;
	
	assert((bit_array_t)index <= ARRAY_LENGTH);	
		
	mask = mask << index;
	
	array |= mask;
	
	return (array);
}

/******************************************************************************/
bit_array_t BitArraySetOff(bit_array_t array, unsigned int index)
{
	bit_array_t mask = 0;
	
	assert((bit_array_t)index <= ARRAY_LENGTH);	
		
	mask = mask << index;
	
	array &= mask;
	
	return (array);
}

/******************************************************************************/
bit_array_t BitArraySetBit(bit_array_t array, unsigned int index, unsigned int value)
{
	bit_array_t mask = value; 
	
	assert((bit_array_t)index <= ARRAY_LENGTH);
	assert(0 == value || 1 == value);	
		
	BitArraySetOff(array, index); /* set off the requested bit */
	
	mask <<= index;
	
	array |= mask; /* setting the bit according to value */
		
	return (array);
}



/******************************************************************************/
bit_array_t BitArrayFlipBit(bit_array_t array, unsigned int index)
{
	bit_array_t mask = 1;
	
	assert((bit_array_t)index <= ARRAY_LENGTH);	
		
	mask = mask << index;
	
	array ^= mask;
	
	return (array);
}


/******************************************************************************/
int BitArrayGetVal(bit_array_t array, unsigned int index)
{
	int value = 0;
	bit_array_t mask = 1;
	
	assert((bit_array_t)index <= ARRAY_LENGTH);	
	
	mask <<= index;
	
	value = array & mask;
	value >>= index;
	
	return (value);
}


/******************************************************************************/
int BitArrayCountOn(bit_array_t array)
{
	int counter = 0;
	
	while(0 != array)
	{
		array = array & (array - 1);
		++counter;
	}
	
	return (counter);
}

/**************/

int BitArrayCountOnLUT(bit_array_t array)
{
	bit_array_t count_bit_on = 0;
	
	static int bit_lut[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1,
	2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
	3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2,
	3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
	4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 
	5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4,
	4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4,
	5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4,
	5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5,
	5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};
	
	/* it check every 8 bits, so it runs 8 times to go over all 64 bits */
	count_bit_on = (bit_lut[array & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 8) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 16) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 24) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 32) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 40) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 48) & MASK_ALL_ON]) +
		 	  (bit_lut[(array >> 56) & MASK_ALL_ON]);
	
	
	
	return (count_bit_on);
}

/******************************************************************************/
int BitArrayCountOff(bit_array_t array)
{
	int counter = 0;
	counter = ARRAY_LENGTH - BitArrayCountOn(array);
	
	return (counter);
}


/******************************************************************************/
bit_array_t BitArrayRotL(bit_array_t array, unsigned int rot_num)
{
	bit_array_t array_mask = array;
	rot_num = (rot_num % ARRAY_LENGTH);
	
	array <<= rot_num;
	
	array_mask >>= (ARRAY_LENGTH - rot_num);
	
	array |= array_mask;
	
	return (array);
}


/******************************************************************************/
bit_array_t BitArrayRotR(bit_array_t array, unsigned int rot_num)
{
	bit_array_t array_mask = array;
	rot_num = (rot_num % ARRAY_LENGTH);
			
	array >>= rot_num;
	
	array_mask <<= (ARRAY_LENGTH - rot_num);
	
	array |= array_mask;
	
	return (array);
}
