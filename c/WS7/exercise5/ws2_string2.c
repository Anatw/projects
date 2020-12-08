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


/* strncpy  /  strncpy */
/***************************************************************
These fonctions copy a string (src) into a destination string (dest).
The n function is a saffer one, which also require he number of characters
the user want to copy.
****************************************************************/

char *Strcpy(char *dest, const char *src)
{
	assert(*dest != '\0');
	assert(*src != '\0');
	while(*src)	
	{
		*dest=*src;
		dest++;
		src++;
	}
	
	return dest;
}


/******/


char *Strncpy(char *dest, const char *src, size_t n)
{
	int i = 0;
	assert(*dest != '\0');
	assert(*src != '\0');
	for (i = 0 ; i <= (int)n && src[i] != '\0' ; i++)	
	{
		*(dest+i) = *(src+i);
	}
	*(dest+i) = '\0';

	return dest;
}



/* Strcasecmp */
/* WORKED WITH SANITY TEST */
/*****************************************************************************
This function compare between two arrays. It ignores difference between upper
and lower cases letters.
*****************************************************************************/

int Strcasecmp(const char *s1, const char *s2)
{
	char *s3 = (char *)s1;
	char *s4 = (char *)s2;
	assert(*s1 != '\0');
	assert(*s2 != '\0');
	
	while(*s3 != '\0' || *s4 != '\0')
	{
		*s3 = tolower(*s3);
		*s4 = tolower(*s4);
	}
	if(*s3 == *s4)
	{
		s3++;
		s4++;
	}
	else
	{
		return(int)(*s3-*s4);
	}
	
	return 0;
}


