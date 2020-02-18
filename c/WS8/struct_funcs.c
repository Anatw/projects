/****************************************************************************

this file was written by Anat Wax on February 18, 2020.
****************************************************************************/

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
	char *intArray = (char *)malloc((sizeof(char) * intLength) + 1);
	if (NULL == intArray)
	{
		printf("problem in malloc (AddInt (STRING)");
	}
	/* I must turn the int from the user into a string so that i can add them
		together */
	
	switch(member->element_type)
	{
	case (INTEGER):
		member->element_value.integer_num += intFromUser;
		break;
	case (FLOAT):
		member->element_value.float_num += (float)intFromUser;
		break;
	case (STRING):
		/* an array for the int from the user: */
		/* turning the int from user into a string */
		sprintf(intArray, "%d", intFromUser);
		intLength = strlen(member->element_value.string) +
			    strlen(intArray) + 1;
		
		member->element_value.string =
			realloc(member->element_value.string,
			sizeof(char) *intLength);
		
		if (NULL == member->element_value.string)
		{
			printf("problem in realloc (AddInt (STRING)");
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
		printf("all dynamicaly allocated memory is freed!\n");
	}
}





