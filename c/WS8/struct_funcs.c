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


void AddInt(element *member, int intFromUser)
{
	int i = 0;
	char *tempPointer = NULL;
	
	/* I must turn the int from the user into a string so that i can add them
		together */
	
	switch(member->element_value.string)
	{
	  	{
			case (INTEGER):
				member.integer_num += intFromUser;
				break;
		}
		{
			case (FLOAT):
				member.float_num += (float)intFromUser;
				break;
		}
		{
			case (STRING):
				strcpy(*tempPointer, array[i].*string);
				array[i].*string = (char*) malloc(length + sizeof(int));
				strcpy(array[i].*string, *tempPointer);
				array[i].*(string + length) = intFromUser;
				break;
		}   
	}
}		


