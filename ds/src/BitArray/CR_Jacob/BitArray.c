/****************************************************************
*          		   Ya'acov Evenchik 24.2.2020                   *
* 				    Bit Array funcs and test	    			*
*                       				              			*
****************************************************************/

#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "BitArray.h"

#define ZERO (48)
#define MAX_SIZE (sizeof(ds_t) * CHAR_BIT)

char *ToString(ds_t a, char *str)
{
	unsigned int i = 0;
			
	for(i = 0; i < MAX_SIZE; ++i)
	{
		str[i] = ((char)(a & 1) + ZERO);
		
		a = a >> 1;
	}
	
	str[i] = '\0';
		
	return (str);
}

/*****************************************************************************/

ds_t SetOn(ds_t a, unsigned int n)
{
	assert((ds_t)n <= MAX_SIZE);
	
	a = a ^ (1UL << n);
		
	return a;
}

/*****************************************************************************/

ds_t SetOff(ds_t a, unsigned int n)
{
	assert((ds_t)n <= MAX_SIZE);
	
	a = a & ~(1UL << n);
	
	return a;
}

/*****************************************************************************/

ds_t SetAll()
{
	return (~(0));
}

/*****************************************************************************/

ds_t SetBit(ds_t a, unsigned int n, unsigned int off_on)
{
	assert((ds_t)n <= MAX_SIZE);
	assert((ds_t)off_on <= 1);
	
	a = SetOff(a, n);
	
	return(a | (off_on << n));
}

/*****************************************************************************/

ds_t ResetAll()
{
	return (0);
}

/*****************************************************************************/

size_t GetVal(ds_t a, unsigned int n)
{
	assert((ds_t)n <= MAX_SIZE);
	
	a = a & (1UL << n);
	a = a >> n;
	
	return (a);
}

/*****************************************************************************/

ds_t FlipBit(ds_t a, unsigned int n)
{
	assert((ds_t)n <= MAX_SIZE);
	
	a ^= (1UL << n);
	
	return (a);
}

/*****************************************************************************/

size_t CountOn(ds_t a)
{
	size_t count = 0;
		
	/*while(0 != a) *//* version without lut *//*
	{
		a = a & (a - 1);
		++count;
	}*/
	
	static int set_bits[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 
	3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 
	2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 
	5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 
	4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 
	4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 
	4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 
	7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 
	4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 
	5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};
	
	/* counting set bits from 64 bits based on 8 bit moves */
	count = set_bits[a & 0xff] +
			set_bits[(a >> 8) & 0xff] +
			set_bits[(a >> 16) & 0xff] +
			set_bits[(a >> 24) & 0xff] +
			set_bits[(a >> 32) & 0xff] +
			set_bits[(a >> 40) & 0xff] +
			set_bits[(a >> 48) & 0xff] +
			set_bits[(a >> 56) & 0xff];
	
	return (count);
}

/*****************************************************************************/

size_t CountOff(ds_t a)
{
	size_t count = 0;
	
	count = CountOn(a);
	count = (MAX_SIZE - count);
	
	return (count);
}

/*****************************************************************************/

ds_t Mirror(ds_t a)
{
	ds_t mirror = 0;
	
	static unsigned int rev_lut[] = 
	{0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 
	0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x8, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 
	0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x4, 0x84, 0x44,
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
	
	/* Reversing integers from 64 bits based on 8 bit moves */
	mirror = (size_t)rev_lut[a & 0xff] << 56 | 
			  (size_t)rev_lut[(a >> 8) & 0xff] << 48 |
			  (size_t)rev_lut[(a >> 16) & 0xff] << 40 |
			  (size_t)rev_lut[(a >> 24) & 0xff] << 32 |
			  rev_lut[(a >> 32) & 0xff] << 24 |
			  rev_lut[(a >> 40) & 0xff] << 16 |
			  rev_lut[(a >> 48) & 0xff] << 8 |
			  rev_lut[(a >> 56) & 0xff];

	return (mirror);
}

/*****************************************************************************/

ds_t RotR(ds_t a, unsigned int t)
{
	unsigned int net_loops = t % MAX_SIZE;
	size_t keep_rotation = 0;
	
	keep_rotation = a;
	a = a >> net_loops; /* push a net_loops time */

	/* add saved area from keep_rotation*/
	a = a | (keep_rotation << (MAX_SIZE - net_loops));
	
	return (a);
}

/*****************************************************************************/

ds_t RotL(ds_t a, unsigned int t)
{
	unsigned int net_loops = t % MAX_SIZE;
	size_t keep_rotation = 0;
		
	keep_rotation = a; 
	a = a << net_loops; /* push a net_loops time */

	/* add saved area from keep_rotation*/
	a = a | (keep_rotation >> (MAX_SIZE - net_loops)); 
		
	return (a);
}

/*****************************************************************************/

int main()
{
	ds_t a = 262144;
	ds_t b = 32;
	char str[65];

	
	
	ToString(a, str);
	printf("\ntostring\t%s\n", str);
	
	b = SetOn(b, 33);
	ToString(b, str);
	printf("\nseton\t%s\n", str);
	
	b = SetOff(b, 33);
	ToString(b, str);
	printf("\nsetoff\t%s\n", str);
	
	b = SetAll(b);
	ToString(b, str);
	printf("\nsetall\t%s\n", str);	


	b = ResetAll();
	ToString(b, str);
	printf("\nresetall\t%s\n", str);
	
	printf("\ngetval\t%ld\n", GetVal(a, 3));
	
	b = SetBit(b, 4, 1);
	ToString(b, str);
	printf("\nsetbit\t%s\n", str);
	
	b = FlipBit(b, 4);
	ToString(b, str);
	printf("\nflipbit\t%s\n", str);
	
	b = 12000;
	b = CountOn(b);
	printf("\ncounton\t%ld\n", b);
	
	b = 32;
	b = CountOff(b);
	printf("\ncountoff\t%ld\n", b);
	
	a = Mirror(a);
	ToString(a, str);
	printf("\nmirror\t%s\n", str);
	
	a = RotR(a, 65);
	ToString(a, str);
	printf("\nrotr\t%s\n", str);
	
	a = RotL(a, 65);
	ToString(a, str);
	printf("\nrotl\t%s\n", str);
	
	
	
	return 0;
}
