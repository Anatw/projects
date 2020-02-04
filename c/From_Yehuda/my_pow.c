/************************************************************************
 * File: my_pow.c														*
 *																		*
 * Purpose: A program that recieves an integer and raises 10 by it.  	*
 ************************************************************************/

#include <stdio.h>

long double pow_ten(int exponent);

int main()
{
	int exponent = 0; // the exponentber to raise 10 by it
	printf("Enter an exponent to raise 10 by its power: ");
	scanf("%d", &exponent);
	printf("\nThe result of 10^%d is: %Lf", exponent, pow_ten(exponent));
	return 0;
}

long double pow_ten(int exponent)
{
	long double result = 1; //the result to return
	/*int is_negative = 0;*/
	long double ten = 10;

	if (exponent < 0)
	{
		exponent *= -1;
		ten = 1 / ten;
	}

	for (int i = 0; i < exponent; i++)
		result *= ten;

	return result;
}
