#include <stdio.h>

int CountBit3(int number);

int main()
{
	int number = 745;
	
	printf("%d\n", CountBit3(number));
	
	return (0);
}

int CountBit3(int number)
{
	int counter = 0;
	
	while(0 != number)
	{
		counter = counter + (number % 2);
		number /= 2;
	}

	return (counter);
}
