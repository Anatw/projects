/****************************************************************************
This program lists the different data types in C(according to the ICO C90),
their names, sizes and the format specifier for each of them.

Writen by Anat Wax, February 2020. Code review was done by Lucy Volkov.
****************************************************************************/
#include <stdio.h>

int main()
{
	printf("name			size\n");
	printf("signed Char:		%d\n", (int)sizeof(signed char));  /* %c*/
	printf("unsigned Char:		%d\n", (int)sizeof(unsigned char));  /*%c */
	printf("\n");
	printf("short int:		%d\n", (int)sizeof(short int));  /*%hd*/
	printf("unsigned short int:	%d\n", (int)sizeof(unsigned short int)); /*%hu*/
	printf("unsigned int:		%d\n", (int)sizeof(unsigned int));  /*%u */
	printf("int:			%d\n", (int)sizeof(int));  /*%d */
	printf("long int:		%d\n", (int)sizeof(long int)); /*%ld*/
	printf("unsigned long int:	%d\n", (int)sizeof(unsigned long int)); /*%lu*/
	printf("\n");
	printf("float:			%d\n", (int)sizeof(float)); /*%f*/
	printf("double:			%d\n", (int)sizeof(double)); /*%lf*/
	printf("long double:		%d\n", (int)sizeof(long double)); /*%Lf*/

	return 0;
}
