#include <stdio.h>
#include "ws2_string.h"
#include <assert.h>
#include <string.h>
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
/* WORKED WITH SANITY TEST */
int Strcasecmp(const char *s1, const char *s2)
{
	char *s3 = (char *)s1;
	char *s4 = (char *)s2;
	while (*s3 && *s4)
	{		
		if((*s3 == *s4) || (*s3 == (*s4 - 32)) || (*s3 == (*s4 + 32)))
		{
			s3++;
			s4++;
		}
		
		else
		{
			return(int)(*s3-*s4);
		}
	}

	return 0;
}


/* strncpy */

char *Strncpy(char *dest, const char *src, size_t n)
{
	int i = 0;
	for (i = 0 ; i <= (int)n && src[i] != '\0' ; i++)	
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
	while (*source)
		{
		*target = *source;
		target++;
		source++;
		}
	*target = '\0';

	return (target - (len));
}




































