#include <stdio.h>

//This function receives an int and flips the order of the digits (12340 becomes 4321).

int flip(int x);

int main()
{
	int n;
	printf("Enter a whole number of more than 3 digits:\n");
	scanf("%d", n);
	
	flip(n);

	return 0;
}

int flip(int x)
{
	int r;
	while(x != 0)
	{
	r = x % 10;
	x /= 10;
	}

	return ;
}

/* 
line11. Please dont use scanf!
line. 19-25 use indentation for blocks.
again please use more informative names. (r,x) 
why more than 3 digits input?
u could make this works even for 1 digit.
waht the function return?
Nice Job!
*/
