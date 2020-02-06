/****************************************************************
*                                                               *
* String.c library       	                                    *
*                       	                                    *
****************************************************************/

#include <stdio.h> /* main C i/o*/
#include <stdlib.h> /* malloc functions*/
#include <string.h>
#include "ws2_string.h"

/***********************************************************************/

int Ws2_Strlen(const char *str) /* str = string to be checked by length*/
{
	int result = 0;

	while(*str++) /* search string upto NULL*/
	{
		result++;
	/*// unneeded space //*/
	}
	
	return result;
}

/***********************************************************************/

int Ws2_Strcmp(const char *str1, const char *str2)
{
	while(*str1 || *str2)
	{
		if (*str1 != *str2)
		{		
		return (*str1-*str2); /* returns numeral ascii difference*/		
		}
		str2++; /*// line should be a tab back //*/
		str1++; /*// line should be a tab back //*/
	}
	return 0;
}

/***********************************************************************/

char *Ws2_Strcpy(char *destination, const char *source)
{
	char *result = destination;
	
	while(*source)
	{ 
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return result;
} 

/***********************************************************************/

char *Ws2_Strncpy(char *destination, const char *source, size_t n)
{
	char *result = destination;
	size_t i = 0;
	for(i = 0; i < n; i++)
	{
		*destination = *source;
		source++;
		destination++;
	}
	*destination = '\0';
	return result;
} 

/***********************************************************************/

int Ws2_Strcasecmp(const char *str1, const char *str2)
{	
	int result = 0;
	
	while(*str1 || *str2)
	{
		/* compare ascii upper vs. lower*/
		if((*str1 == *str2) || (*str1 == *str2 - 32) || (*str1 == *str2 + 32))
		{
		    str1++;
			str2++;
		}
		else 
		{
			/* returns numeral ascii difference*/
			return result = (*str1 - *str2);
		}
		/*// unneeded space //*/
	}
	return result;
}

/***********************************************************************/

const char *Ws2_Strchr(const char *str, int c)
{
    while((*str) && (*str != c))
	{
		str++;
	}
	return str;
}

/***********************************************************************/

char *Ws2_Strdup(const char *str)
{
	
	int leng = (Ws2_Strlen(str));
    	/* create string in correct size*/ 
	char *str_returned = (char*) malloc(sizeof(char) * (leng + 1));
	
	while(*str)
	{
	    *str_returned = *str;
	    str_returned++;
	    str++;
	}
    *str_returned = '\0';
	return str_returned - (leng); /*do not froget to free!!!*/
}

/***********************************************************************/

char *Ws2_Strcat(char *dest, const char *src)
{
	char *returned = dest;
	int leng = (Ws2_Strlen(dest)) + 1;
	dest += leng - 1;
	while(*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return returned;
}

/***********************************************************************/

char *Ws2_Strncat(char *dest, const char *src, size_t n)
{
	size_t i = 0;	
	char *returned = dest;
	int leng = (Ws2_Strlen(dest)) + 1;
	dest += leng - 1;
	
	for(i = 0; i < n; i++)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return returned;
}

/***********************************************************************/

/*str2 = source str1 - destination */
char *Ws2_Strstr(const char *str1, const char *str2) 
{
	size_t leng = Ws2_Strlen(str2);
	while(*str1)
	{
		if (*str1 == *str2)
		{
			str2++;	
		}
		else if(*str2 == '\0')
		{
			return (char*)str1 - leng;
		}
		str1++;		/*// this line should be a tab back //*/		
	}
	return NULL;
} 

/***********************************************************************/

/*str2 = source str1 - destination */
size_t Ws2_Strspn(const char *str1, const char *str2)
{
	size_t found = 0;		
	const char *str1_start = str1;
	while(*str1++)	
		{
			if (*str1 == *str2)
			{
				found++;
				str2++;
				str1 = str1_start;	
			}
			else if(*str2 == '\0')
			{
				return found;
			}	
		}
	return found;	
}

/***********************************************************************/

char *Ws2_Strtok(char *str, const char *delim)
{
	static char *last_loc = 0;
	/*// unneeded space //*/
	
	if(str)
	{
		last_loc = str;
	}
	
	else if(!last_loc)
	{
		return (0);
	}
	
	str = last_loc + strspn(last_loc, delim);
	
	last_loc = str + strcspn(str, delim);
	
	if(last_loc == str)
	{
		return last_loc = 0;
	}
	
	last_loc = *last_loc ? (*last_loc = 0, last_loc + 1) : 0;
		
	return (str);
}































