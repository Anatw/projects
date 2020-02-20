/*******************************************************************************
					  	 Written by Anat Wax
						  February 20, 2020
						Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* atoi */
#include <string.h> /* stlen() */

#define BASE (2)
#define ASCII (48) /* ascii '0' = 48 */

char *Itoa(int number, int base, char *stringOfInt, int intLength);
void swap(char *x, char *y);
char *reverse(char *reverseAray, int j, int index);
int NumInInt(int intFromUser);

int main()
{
	int number = 71;
	int intLength = NumInInt(number);
	char *stringOfInt = (char *)malloc((sizeof(char) * intLength) + 1);
	int base = 36;
	
	Itoa(number, base, stringOfInt, intLength);
	
	printf("the string: %s\n", stringOfInt);
	
	return (0);
}

char *Itoa(int number, int base, char *stringOfInt, int intLength)
{
	int index = 0;
	int modulus = 0;
	int is_negative = 0;
	
	if(number < 0)
	{
		is_negative = (-1);
	}
	
	if(0 == number)
	{
		*stringOfInt = '\0';
		return stringOfInt;
	}

	if((2 <= base) || (base <= 36))
	{
		while(0 != number)
		{
			modulus = number % base;
			
			if(modulus > 9)
			{
				stringOfInt[index] = (modulus - 10) + 'A';
				++index;
			}
			else
			{
				stringOfInt[index] = modulus + '0';
				++index;
			}
			number = number / base;
		}
	}
	else
	{
		return stringOfInt;
	}
	
	if((-1) == is_negative)
	{
		*stringOfInt = '-';
	}
	
	stringOfInt[index] = '\0';
	reverse(stringOfInt, 0, (index - 1));
	
	return stringOfInt;
}

/* inline function to swap two numbers */
void swap(char *x, char *y) 
{
	char t = '0'; 

	t = *x; 
	*x = *y;
	*y = t;
}

/* function to reverse buffer[i..j] */
char *reverse(char *reverseAray, int j, int index)
{
	while (j < index)
	{
		swap(&reverseAray[j], &reverseAray[index]);
		++j;
		--index;
	}
	
	return reverseAray;
}

int NumInInt(int intFromUser)
{
	int counter = 0;
	
	while(0 != intFromUser)
	{
		++counter;
		intFromUser /= 10;
	}
	
	return counter;
}


