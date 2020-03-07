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


/* strncpy  /  strncpy */
/***************************************************************
These fonctions copy a string (src) into a destination string (dest).
The n function is a saffer one, which also require he number of characters
the user want to copy.

****************************************************************/

char *Strcpy(char *dest, const char *src)
{
	char *dest_start = dest;
	
	assert(*dest != '\0');
	assert(*src != '\0');
	
	while(*src)	
	{
		*dest=*src;
		dest++;
		src++;
	}
	
	*dest = '\0';
	
	return dest_start;
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


/* strstr */
/********************************************************************
This finction locates a sub-string (search_str) in a string.
*********************************************************************/

char *Strstr(const char *string, const char *search_str)
{
	int counter = 0;
	const char *start_string = search_str;
	char *start = NULL;
	assert(*string != '\0');
	assert(*search_str != '\0');
	
	while(*string)
	{
		if(*string == *search_str)
		{
			counter = 0;
			start = (char *)string;
			while (*string == *search_str)
			{
				++string;
				++search_str;
				++counter;
			}
			if (*search_str == '\0')
			{
				return (char *)(start);
			}
			else
			{
				search_str = start_string;
				string -= counter;
			}
		}
		++string;
	}
	return (char *)(start);
}



/* strspn */
/*****************************************************************************
This function search for the specific characters (accept) in a string (s).
When it reaches a letter in "accept" that it canno't locate in string - it
quits the function and return the number of letter from "s" that it has found.
******************************************************************************/

char Strspn(const char *s, const char *accept)
{
	size_t counter = 0;
	const char *accept_start = accept;
	assert(*s != '\0');
	assert(*accept != '\0');
	
	for (; *s ; ++s)
	{
		int isfound = 0 ; /*boolean */
		accept = accept_start; /*saves the pointer to the start of accept */
		while (*accept && !isfound)
		{
			if (*accept == *s)
			{
				counter++;
				isfound = 1;
			}
			else
			{
				accept++;
			}
		}
		if (*accept == '\0')
		{
			return (counter);
		}
	}
	return (counter);
}



/* strtok */
/********************************************************************
char *strtok(char *str, const char *delim);
seperate a string to different tokn when bump into a character from
the delim.
*********************************************************************/

char *Strtok(char *str, const char *delim)
{
	static char *p = 0;
	assert(*str != '\0');
	assert(*delim != '\0');
	if(str) /* assign str to p if str is not null */
	{
		p = str;
	}
	else if (!p) /* return 0 if there are no tokens left */
	{
		return (0);
	}
	/* str jumps over all the delemiters to the next token */
	str = p + Strspn(p, delim);				
	p = str + strcspn(str, delim); /* p jumps to the next delimiter */
	if (p == str)
	{
		return p = 0; /* return 0 if there are no tokens left */
	}
	
	/* if there is a delimeter in *p, change it to 0 and step over.
	else set p to 0 */
	p = *p ? (*p = 0, p + 1) : 0;
	
	return(str); /* return the token*/
}



/* IsPalindrome */
/********************************************************************
This function find if an entered string is a palindrome.

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
			return 0; /* string is not palindrome */
		}
	}
	return 1; /* string is palindrome */
}



/* add_num */
/*************************************************************************
This function sums the addition of two chars of integers, and returns the
result.
**************************************************************************/

void WS2_strrev(char *str)
{
	int i = 0;
	int j = 0;
	char tmp = '\0';
	int len = strlen(str);
	assert(*str != '\0');
	
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}

/***		*/
char *add_num(const char *num1, const char *num2)
{
	int tmp = 0;
	int reslen = 0;
	int num1len = strlen(num1);
	int num2len = strlen(num2);
	int larg = num1len > num2len ? num1len : num2len;
	char *resault = (char*)calloc((larg + 2) , sizeof(char));
	
	assert(*num1 != '\0');
	assert(*num2 != '\0');
	
	if (!resault)
	{
		printf("%s\n", "calloc allocation error");
		abort();
	}
	num1len--;
	num2len--;
	
	while (num1len >= 0 && num2len >= 0)
	{
		tmp += (num1[num1len] - 48) + (num2[num2len] - 48);
		resault[reslen] = (tmp % 10) + 48;
		tmp /= 10;
		reslen++;
		num1len--;
		num2len--;
	}	
	
	if (num1len >= 0 && num2len >= 0)
	{
		if (tmp > 0)
		{
			resault[reslen] = (tmp % 10) + 48;
			reslen++;
		}
	}
	else if (num1len >= 0)
	{
		while (tmp && num1len >= 0)
		{
			tmp += (num1[num1len] - 48);
			resault[reslen] = (tmp % 10) + 48;
			tmp /= 10;
			reslen++;
			num1len--;
		}
		
		if (tmp)
		{
			resault[reslen] = (tmp % 10) + 48;
			reslen++;
		}
		else
		{
			while (num1len >= 0)
			{
				resault[reslen] = num1[num1len];
				reslen++;
				num1len--;
			}
		}
	}
	else
	{
		while (tmp && num2len >= 0)
		{
			tmp += (num2[num2len] - 48);
			resault[reslen] = (tmp % 10) + 48;
			tmp /= 10;
			reslen++;
			num2len--;
		}
		
		if (tmp)
		{
			resault[reslen] = (tmp % 10) + 48;
			reslen++;
		}
		else
		{
			while (num2len >= 0)
			{
				resault[reslen] = num2[num1len];
				reslen++;
				num2len--;
			}
		}
	}
	resault[reslen] = '\0';
	WS2_strrev(resault);

	return resault;
}


/* SEVEN_BOOM */
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


/* RmSpaces */
/********************************************************************
This function accepts a string and returns the same string after deliting 
spaces (' '), double-spaces ('  '), and tabs ('\t') from the string.
If a double-space is located within the string, each double-space is
transformed into a single space.
*********************************************************************/

void RmSpaces(char *str)
{
	char *read = str;
	char *write = str;
	assert(*str != '\0');
		
	if(*str == ' ' || *str == '\t')
	{
		read++;
	}
	
	while(*read)
	{
		if(!(*read == ' ' || *read == '\t'))
		{
			*write = *read;
			read++;
			write++;
		}
		else
		{
			*write = ' ';
			++write;
			++read;
			read = read + strspn(read, " \t");
		}
	}
	if(*(write - 1) == ' ')
	{
		*(write -1) = '\0';
	}
	else
	{
	*write = '\0';
	}
}


/* swap_pointers_pointers */
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




