/*******************************************************************************
					  		Written by Anat Wax
						 	April fth-6th, 2020
						   Reviewer: Noffar Gil
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#define STRING_SIZE (2000)

/* 
 * Strlen: get the length of a string recursively.
 * Arguments: string - pointer to a string
 * Return: size_t with the size
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
size_t Strlen(char *string);

/* 
 * Strcmp: compare two strings recursively.
 * Arguments: string1, string2 - pointers to strings to compare
 * Return: - 0 if the strings equal.
 * 		    else, returns the ascii difference in the first different letter,
 * 			that will be:
 *		   - different latter in string1 is smaller than string2.
 *		   - different latter in string1 is larger than string2.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int Strcmp(char *string1, char *string2);

/* 
 * Strcpy: Copy string from source to destination.
 * Arguments: destination - pointer to the starting point of the destination
 * 						    for copy.
 *            source - pointer to the string to be coppied.
 * Return: pointer to destination.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
char *Strcpy(char *destination, char *source);

/* 
 * Strcat: Concatenate two strings.
 * Arguments: destination - pointer to the starting point of the new string.
 * 							I'ts size must be adequate for both strings.
 *            source - the string to be added right after destination.
 * Return: pointer to destination.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
char *Strcat(char *destination, char *source);

/* 
 * Strstr: Check for occurrence of str2 (needle) in str1(haystack).
 * Arguments: haystack - string to search in.
 *            needle - string to search in str1(haystack).
 * Return: a pointer to the first occurrence of str2 in str1, 
 * 		   or a NULL pointer if str2 is not part of str1.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
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
	return (Strlen(++string));
}

/******************************************************************************/

int Strcmp(char *string1, char *string2)
{
	if (*string1 != *string2)
	{
		return (*string1 - *string2);
	}
	else if ('\0' == *string1 && '\0' == *string2)
	{
		return (0);
	}
	
	return (Strcmp(++string1, ++string2));
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
		
	if ('\0' == *source) /* add fix fot rhe case of {'1', '2', 0, '6', '7'}; */
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
