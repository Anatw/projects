/*******************************************************************************
		  	    Written by Anat Wax
			     February 20, 2020
			   Reviewer: Noffar Gil
*******************************************************************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free(), strtol(), exit() */

#define NEGATIVE (-1)

char *Itoa(int number, int base, char *string_of_int);
void swap(char *x, char *y);
char *reverse(char *reverse_array, int j, int index);
int NumInInt(int int_num);

int main(int argc, char *argv[])
{
	char *p = NULL;
	int base = 1;
	int number = 99;
	int int_length = NumInInt(number);
	char *string_of_int = (char *)malloc((sizeof(char) * int_length) + 1);
	
	if(1 == argc)
	{
		printf("you must enter a base!\n");
		exit(1);
	}
	else
	{
		base = (int)strtol(argv[1], &p, 10);
	}	
	
	Itoa(number, base, string_of_int);
	
	printf("the string: %s\n", string_of_int);
	
	free(string_of_int);
	return (0);
}

char *Itoa(int number, int base, char *string_of_int)
{
	int index = 0;
	int modulus = 0;
	int is_negative = 0;
	
	if(number < 0)
	{
		is_negative = NEGATIVE;
	}
	
	if(0 == number)
	{
		*string_of_int = '\0';
		return string_of_int;
	}

	if((2 <= base) || (base <= 36))
	{
		while(0 != number)
		{
			modulus = number % base;
			
			if(modulus > 9)
			{
				string_of_int[index] = (modulus - 10) + 'A';
				++index;
			}
			else
			{
				string_of_int[index] = modulus + '0';
				++index;
			}
			number = number / base;
		}
	}
	else
	{
		return string_of_int;
	}
	
	if(NEGATIVE == is_negative)
	{
		*string_of_int = '-';
	}
	
	string_of_int[index] = '\0';
	reverse(string_of_int, 0, (index - 1));
	
	return string_of_int;
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
char *reverse(char *reverse_array, int j, int index)
{
	while (j < index)
	{
		swap(&reverse_array[j], &reverse_array[index]);
		++j;
		--index;
	}
	
	return reverse_array;
}

int NumInInt(int int_num)
{
	int counter = 0;
	
	while(0 != int_num)
	{
		++counter;
		int_num /= 10;
	}
	
	return counter;
}
