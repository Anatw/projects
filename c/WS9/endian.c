#include <stdio.h>
#include <string.h>

int main()
{
	short int number = 1;
	/* 00000000 00000001 */

	if(0 == (unsigned char)number)
	{
		printf("This system is Little Endian\n");
	}
	else
	{
		printf("This system is Big Endian\n");
	}
	
	return (0);
}
