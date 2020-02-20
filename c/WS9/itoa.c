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

char Itoa(int number, int base, char *stringOfInt);
void swap(char *x, char *y);
char *reverse(char *reverseAray, int j, int index);
int NumInInt(int intFromUser);

int main()
{
	int number = -1234;
	int intLength = NumInInt(number);
	char *stringOfInt = (char *)malloc((sizeof(char) * intLength) + 1);
	int base = 2;
	
	Itoa(number, base, stringOfInt);
	
	printf("the string: %s\n", stringOfInt);
	
	return (0);
}

char Itoa(int number, int base, char *stringOfInt)
{
	int index = 0;
	int modulus = 0;
	
	if(0 == number)
	{
		*stringOfInt = '\0';
		return *stringOfInt;
	}
	else if(base < 0 || 10 == base)
	{
		sprintf(stringOfInt, "%d", number);
		if(10 == base)
		{
			return *stringOfInt;
		}
		else
		{
			stringOfInt[index + 1] = '-';
			return *stringOfInt;
		}
	}
	else if((2 <= base) || (base <= 36))
	{
		modulus = number % base;
		
		if(modulus < 9)
		{
			stringOfInt[index] = (modulus - 10) + 'A';
		}
		else
		{
			stringOfInt[index] = modulus + '0';
		}
		stringOfInt[index] = '\0';
	}
	
	reverse(stringOfInt, 0, index);
	
	return *stringOfInt;
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


