/************************************************************************************
 * File: swap.c																		*
 *																					*
 * Purpose: A function that recieves to pointer integers and swaps their values  	*
 ************************************************************************************/

#include <stdio.h>

void swap(int *a, int *b);

int main()
{
	int a = 5987;
	int b = -758;
	printf("a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("SWAPED! a = %d, b = %d\n", a, b);
	return 0;
}

void swap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
