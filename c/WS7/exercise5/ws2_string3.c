/****************************************************************************
This file was written by anat Wax on the week starting on Fabruary 2nd 2020.
the code review was done by Nofar Gil on February 6th.

All functions `main'
collect2: error: l names sart with an upper-case S (unlike the funciton in string.h).
****************************************************************************/
#include <stdio.h>
#include "ws2_string.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>




/* Strchr */
/********************************************************************
returns a pointer for thr first appearencr of the entered character.
*********************************************************************/

char *Strchr(char *str, int character)
{
	assert(*str != '\0');
	while(*str)
	{
		if(*str == character)
		{
			return str;
		}
		else
		{
			++str;
			
		}
	}
	str = '\0';
	return str;
}


/* strdup */
/********************************************************************
*  strdup copy a string from the source string to the target string.
*  the target is created using malloc by the function itself.
*  the user must free the memory space allocated by the function 
*********************************************************************/

char *Strdup(char source[])
{
	size_t len = Strlen(source);
	char *target = malloc((len + 1) * sizeof(char));
	if(target != 0)
	{
		while (*source)
		{
			*target = *source;
			target++;
			source++;
		}
		*target = '\0';
		return (target - len);
	}
	else
	{
		return 0;
	}
}



/* Strcat  /  Strncat */
/********************************************************************
append the src string to the dest string. The user is in charge that
the dest sting is big anough to hold both strings!
*********************************************************************/

char *Strcat(char *dest, const char *src)
{
	char *temp = dest;
	dest = dest + ((int)Strlen(dest));
	assert(*dest != '\0');
	assert(*src != '\0');
	
	while(*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return temp;
}


/******/

