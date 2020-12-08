#include <stdio.h>

//This function receives an int and flips the order of the digits (12340 becomes 4321).

int flip(int x);

int main()
{
	int n;
	printf("Enter a whole number of more than 3 digits:\n");
	scanf("%d", &n);
	printf("Number before flip: %d\n", n);
	
	int flipped_number = flip(n);
	printf("The flipped number is: %d \n", flipped_number);

	return 0;
}

int flip(int x)
{
	int new_number = 0;
	while(x != 0)
	{
	new_number = (x % 10) + (new_number * 10);
	x /= 10;
	}

	return new_number;
}
