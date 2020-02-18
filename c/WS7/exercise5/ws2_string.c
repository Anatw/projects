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



/* strlen */
/***************************************************************
Variable Length Parameter: Return the length of the string s.
WORKED WITH SANITY TEST
****************************************************************/

size_t Strlen(char *s)
{
	size_t i = 0;
	assert(*s != '\0'); /*pointer must not be empty... */
	while (s[i] != '\0')	
	{
		i++;
	}
	return i;
}


/* strcmp */
/***************************************************************
Compare two strings
WORKED WITH SANITY TEST
****************************************************************/

int Strcmp(const char *s1, const char *s2)
{
	assert(*s1 != '\0');
	assert(*s2 != '\0');
	if ((*s1 && *s2) != '\0')
	{		
		while (*s1 == *s2)
		{
			s1++;
			s2++;
		}
	}
	return(int)(*s1-*s2);
}


