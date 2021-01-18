#include <stdio.h>

//This fun receives an int, n, and returns 10^n.

float power(float x);

int main()
{
	float n;

	printf("Enter a whole number:\n");
	scanf("%f",&n);

	float result = power(n);

	printf("%f\n", result);

	return 0;
}

float power(float x)
{
	int i;
	float t = 10;
	float r = 1;

	if (x<0)
	{
	t = 1/t;
	x = x*(-1);
	}
	
	for (i = 0 ; i < x ; i++)
	{
	r *= t;
	}
	
	return r;
}
