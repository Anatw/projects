/*******************************************************************************
					  	 Written by Anat Wax
						  February 18, 2020
						Reviewer: Lusy Volkov
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main_funcs.h"
#include "struct_funcs.h"

void Printush(element *member)
{
	switch(member->element_type)
	{
	  	case (INTEGER):
			printf("Integer: %d\n",member->element_value.integer_num);
			break;
		case (FLOAT):
			printf("float: %f\n",member->element_value.float_num);
			break;
		case (STRING):
			printf("string: %s\n",member->element_value.string); 
			break; 
	}
}


int NumInInt(int intFromUser)
{
	int counter = 0;
	
	while(0 != intFromUser)
	{
		++counter;
		intFromUser /= 10;
	}
	
	return counter;
}


void AddInt(element *member, int intFromUser)
{
	int intLength = NumInInt(intFromUser);
	
	/* allocating memory for the int from the user, turned into a string: */
	char *intArray = (char *)malloc((sizeof(char) * intLength) + 1);
	
	if (NULL == intArray)
	{
		printf("problem in malloc (AddInt (STRING)");
	}
	
	switch(member->element_type)
	{
		case (INTEGER):
			member->element_value.integer_num += intFromUser;
			free(intArray);
			intArray = NULL;
			break;
		case (FLOAT):
			member->element_value.float_num += (float)intFromUser;
			free(intArray);
			intArray = NULL;
			break;
		case (STRING):
			/* turning the int from user into a string: */
			sprintf(intArray, "%d", intFromUser);
			intLength = strlen(member->element_value.string) +
					    strlen(intArray) + 1;
			member->element_value.string =
						realloc(member->element_value.string,
						sizeof(char) *intLength);
			
			if (NULL == member->element_value.string)
			{
				printf("problem in realloc (AddInt (STRING))");
			}
			else
			{
				strcat(member->element_value.string, intArray);
			
			free(intArray);
			intArray = NULL;
			
			break;
			}
	}
}		


void Cleanup(element *member)
{
	switch(member->element_type)
	{
		case (INTEGER): case (FLOAT):
			break;
		case (STRING):
			free(member->element_value.string);
			member->element_value.string = NULL;
			break;
	}
	
	printf("all dynamicaly allocated memory is freed!\n");
}





