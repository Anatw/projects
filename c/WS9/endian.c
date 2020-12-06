/*******************************************************************************
This function check if the machine is in the format of big endian (meaning
that the most important data is stored in the smaller mempry address (1000))
or little endian (the most important data is stored in the bigger address
(0001));
		    	    Written by Anat Wax
			     February 20, 2020
			   Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h>	/* printf() */

/* endian in macro: */
#define WHICH_ENDIAN() {short int x = 1; \
	(0 == x) \
	? printf("This system is Big Endian\n") \
	: printf("This system is Little Endian\n") ;}


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
		printf("This system is Big Endian\n");
	}
	else
	{
		printf("This system is Little Endian\n");
	}
}
