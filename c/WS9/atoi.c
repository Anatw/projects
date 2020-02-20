/*******************************************************************************
					  	 Written by Anat Wax
						  February 20, 2020
						Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* atoi */
#include <string.h> /* stlen() */

#define BASE (2)
#define ASCII (48) /* ascii '0' = 48 */

int Atoi(char *string);

int main()
{
	char *string = "71";
	/* char *p = NULL; */
	
	printf("atoi: %d\n", atoi(string));
	/* printf("strtol: %ld\n", strtol(string, &p, 8)); */
	printf("Atoi: %d\n", Atoi(string));
		
	return (0);
}

/* implement string to int function for base 10 */
int Atoi(char *string)
{
	int number = 0;
	int index = 0;
	
	if('-' == string[index])
	{
		index = 1;
	}
	
	for(; index < (int)strlen(string); ++index)
	{
		number = (string[index] - ASCII) + (number * BASE);
	}
	
	if('-' == string[0])
	{
		return (number *= (-1));
	}
	else
	{
		return (number);
	}
	
}
