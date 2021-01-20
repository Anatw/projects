/*******************************************************************************
Written by Anat Wax, anatwax@gmail.com
February 2020
*******************************************************************************/
#include <stdio.h>
#include "ws2_string.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ZERO (48)


char *Strncat(char *dest, const char *src, size_t n)
{	
	int counter = 0;
	char *temp = dest;
	assert(*dest != '\0');
	assert(*src != '\0');
	
	dest = dest + ((int)strlen(dest));

	while(*src && counter < (int)n)
	{
		*dest = *src;
		++dest;
		++src;
		++counter;
	}
	*dest = '\0';
	return temp;
}


/********************************************************************
Strstr - Locates a sub-string in a string.
return - pointer to the beginning of the substring in the destinartion string.
*********************************************************************/
char *Strstr(const char *string, const char *search_str)
{
	int counter = 0;
	const char *to_search = search_str;
	char *start = NULL;
	assert(*string != '\0');
	assert(*search_str != '\0');
	
	while(*string)
	{
		if(*string == *to_search)
		{
			counter = 0;
			start = (char *)string;
			
			while (*string == *to_search)
			{
				++string;
				++to_search;
				++counter;
			}

			if (*to_search == '\0')
			{
				return (start);
			}
			else
			{
				to_search = search_str;
				string -= counter;
			}
		}

		++string;
	}

	return (start);
}


/********************************************************************
This function find if an entered string is a palindrome.
Return:
1 - string is a palindrome.
0 - string is not palindrome.
*********************************************************************/
int IsPalindrome(const char *str)
{
	int length = strlen(str);
	char *from_end = (char *)str + length - 1;
	assert(*str != '\0');
	
	while (str < from_end)
	{
		if (*str == *from_end)
		{
			--from_end;
			++str;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}


/********************************************************************
This function accept a range of numbers (frm, to) and return the numbers,
unless a number contain the digit "7" or can be divised by 7 with no remsinder.
*********************************************************************/
void SEVEN_BOOM(int from, int to)
{	
	int number = 0;
	for(number = from ; number < to ; ++number)
	{
		if(((number % 7) == 0) || has_seven(number))
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n", number);
		}
	}
}
	
int has_seven(int number)
{
	while(number > 0)
	{
		if(number % 10 == 7)
		{
			return 1;
		}
		else
		{
			number /= 10;
		}
	}
	return 0;
}



/*******************************************************************************
Function accepts char *.
Return the same string after deleting spaces (' '), double-spaces ('  '), and tabs ('\t') from the string. If a double-space is located within the string, each double-space is transformed into a single space.
*******************************************************************************/
void RmSpaces(char *str)
{
	char *read = str;
	char *write = str;
	assert(*str != '\0');
		
	if(*str == ' ' || *str == '\t')
	{
		++read;
	}
	
	while(*read)
	{
		if(!(*read == ' ' || *read == '\t'))
		{
			*write = *read;
			++read;
			++write;
		}
		else
		{
			*write = ' ';
			++write;
			++read;
			read = read + strspn(read, " \t");
		}
	}

	if (*(write - 1) == ' ')
	{
		*(write -1) = '\0';
	}
	else
	{
	*write = '\0';
	}
}


/********************************************************************
this function swapps between two pointers to int (by usind pointers
to pointers).
*********************************************************************/
void swap_pointers_pointers(int **pp1, int **pp2)
{
	int *p = *pp1;
	*pp1 = *pp2;
	*pp2 = p;
	assert(**pp1 != '\0');
	assert(**pp2 != '\0');
}	
