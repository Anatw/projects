/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#define STRING_SIZE (2000)

size_t Strlen(char *string);

int Strcmp(char *string1, char *string2);

char *Strcpy(char *destination, char *source);

char *Strcat(char *destination, char *source);

char *Strstr(char *haystack, const char *needle);

/************************************************/

int main ()
{
	char string1[23] = "what a beautiful day";
	char *string2 = "what a lovely day";
	char string3[20] = {0};
	char *string4 = "be";
	char *string5 = "lo";
	
	printf("%ld\n", Strlen(string1));
	printf("%d\n", Strcmp(string1, string2));
	Strcpy(string3, string2);
	printf("%s\n", string3);
	Strcat(string1, string4);
	printf("%s\n", string1);
	printf("%s\n", Strstr(string2, string5));	
	
	return (0);
}

/******************************************************************************/

size_t Strlen(char *string)
{
	static size_t counter = 0;
	size_t result = 0;

	if ('\0' == *string)
	{
		result = counter;
		counter = 0;
		
		return (result);
	}
	
	++counter;
	Strlen(++string);
}

/******************************************************************************/

int Strcmp(char *string1, char *string2)
{
	if (string1 != string2)
	{
		return (0);
	}
	
	if ('\0' != *string1 && '\0' != *string2)
	{
		return (1);
	}
	
	Strcmp(++string1, ++string2);
}

/******************************************************************************/

char *Strcpy(char *destination, char *source)
{
	static size_t counter = 0;
	
	if ('\0' == *source)
	{
		return (destination - counter);
	}
	
	assert('\0' == *destination);
	*destination = *source;
	++counter;
	
	return (Strcpy(++destination, ++source));
}

/******************************************************************************/

char *Strcat(char *destination, char *source)
{
	static int counter = 0;
		
	if ('\0' == *source)
	{
		return (destination - counter);
	}

	if ('\0' != *destination)
	{
		++counter;
		return (Strcat(++destination, source));
	}
	
	++counter;

	*destination = *source;
	
	return (Strcat(++destination, ++source));
}

/******************************************************************************/

/*
 * haystack − This is the main C string to be scanned.
 * needle − This is the small string to be searched within haystack string.
 * the function can handle strings which length is up to 2000 chars.
 */
char *Strstr(char *haystack, const char *needle)
{
	/* if haystack and needle are partialy equal - reset heystack */
	static size_t count_reset = 0; 
	static size_t counter = 0; /* general counter */
		
	assert(haystack);
	assert(needle);
	
	if (*needle == '\0')
	{
		return (haystack - counter);
	}
	
	if (*haystack == *needle)
	{
		++counter;
		return (Strstr(++haystack, ++needle));
	}
	else
	{
		count_reset = counter;
		counter = 0;
		return (Strstr(++haystack, needle - count_reset));
	}
}


/*************************** functions graveyard ******************************/
/*char *Strstr(char *haystack, char *needle)
{
	char string[STRING_SIZE] = {0};
	char *p_string = string;
	static int counter = 0;
	static int needle_length = 0;
	int status = 0;
	
	if (0 == status)
	{
		needle_length = (int)Strlen(needle);
		status = 1;
	}
	
	if (needle_length == counter)
	{
		haystack -= counter;
		return (Strcpy(++p_string, ++haystack));
		
		if ('\0' == *haystack)
		{
			*p_string = '\0';
			return (string);
		}
	}
	
	if (*haystack == *needle && '\0' != *needle)
	{
		++counter;
		Strcmp(++haystack, ++needle);
		Strstr(++haystack, ++needle);
	}
	else
	{	
		Strstr(++haystack, needle);
	}
	
	if ('\0' == *haystack)
	{
		return (haystack - counter);
	}
}*/
