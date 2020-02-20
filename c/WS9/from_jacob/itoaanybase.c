#include <stdio.h>
#include <stdlib.h>

/* inline function to swap two numbers */
void swap(char *x, char *y) 
{
	char t = '0'; 

	t = *x; 
	*x = *y;
	*y = t;
}

/* function to reverse buffer[i..j] */
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
	{
		swap(&buffer[i], &buffer[j]);
		++i;
		--j;
	}
	
	return buffer;
}

/* implementation of itoa() function in C */
char* itoa(int value, char* buffer, int base)
{
	int absolute_val = 0; 
	int i = 0;
	int reminder = 0;
	
	absolute_val =	abs(value); /* absolute value of num */
	
	/* does not work under base 2 and above base 36 */
	if (base < 2 || base > 36)
	{
		return buffer;
	}
		
	while (0 != absolute_val)
	{
		reminder = absolute_val % base;

		if (reminder >= 10) 
		{
			buffer[i] = 'A' + (reminder - 10);
			++i;
		}
		else
		{	
			buffer[i] = '0' + reminder;
			++i;
		}
		
		absolute_val = absolute_val / base;
	}

	/* enters only if number is 0 */
	if (0 == i)
	{	
		buffer[i] = '0';
		++i;
	}
	
	/* If base is 10 and value is negative adds '-' */
	if (value < 0 && base == 10)
	{	
		buffer[i] = '-';
		++i;
	}
	
	buffer[i] = '\0'; /* null at end of string */

	/* reverse the string and return it */
	return reverse(buffer, 0, i - 1);
}


int main(void)
{
	char buffer[33];
	
	int value = 71;
	int base  = 36;
	
	itoa(value, buffer, base);
	
	printf("%s\n", buffer);

	return 0;
}
