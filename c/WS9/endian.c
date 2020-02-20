/*******************************************************************************
					  	 Written by Anat Wax
						  February 20, 2020
						Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h>
#include <string.h>

/* endian in macro: */
#define WHICH_ENDIAN() {short int x = 1; \
	(x == 0) \
	? printf("This system is Little Endian\n") \
	: printf("This system is Big Endian\n");}


/* endian in function: */
void WhichEndian(short int number);

int main()
{
	short int number = 1;
	/* 00000000 00000001 */
	printf("using macro:\n");
	WHICH_ENDIAN();
	
	printf("\nusing function:\n");
	WhichEndian(number);
	
	return (0);
}

void WhichEndian(short int number)
{
	if(0 == (unsigned char)number)
	{
		printf("This system is Little Endian\n");
	}
	else
	{
		printf("This system is Big Endian\n");
	}
}
