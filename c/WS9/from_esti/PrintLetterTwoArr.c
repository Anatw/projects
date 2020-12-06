/******************************************************************************
* File:                                                         * 
* Auther: Esti Binder                                                         *
* Reviewed by:                                                                *
* Description:                                                 *
*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define RANGE_CHAR (123)

enum status 
{
	EMPTY,
	STR1,
	STR2
};

void PrintLetterTwoStr(char *str1, char *str2, char *str3)
{
	
	size_t i = 0;
	size_t sizeStr1 = strlen(str1);
	size_t sizeStr2 = strlen(str2);
	size_t sizeStr3 = strlen(str3);		
	int StatusArr[RANGE_CHAR];
	
	for (; i < RANGE_CHAR; ++i)
	{
		StatusArr[i] = EMPTY;
	}
	
	for (i = 0; i < sizeStr1; ++i)
	{	
		StatusArr[(int)(str1[i])] = STR1;
	}
	
	for (i = 0; i < sizeStr2; ++i)
	{
		if (STR1 == StatusArr[(int)(str2[i])])
		{
			StatusArr[(int)(str2[i])] = STR2;
		}
	}
	
	for (i = 0; i < sizeStr3; ++i)
	{
		if (EMPTY != StatusArr[(int)(str3[i])])
		{
			StatusArr[(int)(str3[i])] = EMPTY;
		}	
	}

	
	for (i = 0; i < RANGE_CHAR; ++i)
	{
		if (STR2 == StatusArr[i])
		{
			printf("%c\n", (char)i);
		}	
	}
}

int main()
{
	
	char str1[100] = "abgslkjc";
	char str2[100] = "cfsfddkja";
	char str3[100] = "fbcweokc";

	PrintLetterTwoStr(str1, str2, str3);
	
	return (0);
}
