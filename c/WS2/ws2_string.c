#include <stdio.h>
#include "ws2_string.h"
#include <assert.h>

#include <stdlib.h>


/* strlen */
/*Variable Length Parameter: Return the length of the string s. */
/* WORKED WITH SANITY TEST */
size_t Strlen(char *s)
{
	size_t i = 0;
	while (s[i] != '\0')	
	{
	i++;
	}
	return i;
}


/* strcmp */
/* Compare two strings */
/* WORKED WITH SANITY TEST */
int Strcmp(const char *s1, const char *s2)
{
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

/* Strcasecmp */
/* working... BUT NOT AS EXPECTED */
int Strcasecmp(const char *s1, const char *s2)
{
	char *s3 = (char *)s1;
	char *s4 = (char *)s2;
	while ((*s3 && *s4) != '\0')
	{		
		if(122>*s3>97 || 122>*s4>97 && (((*s3-*s4)*(*s3-*s4)) == 32*32) )
		{
			s3++;
			s4++;
		}
		
		else ((*s3-*s4)==0);
		{
			s3++;
			s4++;
		}
	}
	return(int)(*s3-*s4);
}


/* strncpy */

char *Strncpy(char *dest, const char *src, size_t n)
{
	int i = 0;
	for (i = 0 ; i <= n && src[i] != '\0' ; i++)	
	{
		*(dest+i) = *(src+i);
	}
	*(dest+i) = '\0';

	while ((n - i) > 0)
	{
		*(dest+i) = '\0';
		i++;
	}
	return dest;
}
