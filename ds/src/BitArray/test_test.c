#include <stdio.h>

int CountOn(int array);

int main()
{
	int i = 0;
	
	for (i = 0; i < 256; ++i)
	{
		printf("%d, ",CountOn(i));
	}
	
	return (0);
}

int CountOn(int array)
{
	int counter = 0;
	
	while(0 != array)
	{
		array = array & (array - 1);
		++counter;
	}
	
	return (counter);
}
