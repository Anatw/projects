/******************************************************************************
							   File: ImpleMacro 
							   					
							Written by: Noffar Gil
							Review by:Yehuda Levavi
								Date: 18.02.2020

*******************************************************************************/



#include <stdio.h> /* printf() */
#include <stdlib.h>

#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define MAX3(a, b, c) (((MAX2(a, b)) > (c)) ? (MAX2(a, b)) : (c))

#define SIZEOF(var) (char *)(&var + 1) - (char *)(&var)

#define TYPE_SIZEOF(type) \
			(((char *) (1 + ((type *) 0))) - ((char *) ((type *) 0)))
						
/* 
	type is like a local variable to the macro.
	&type give the address of a variable declared in the program/
	increment with 1 gives the address where the next variable of type x 
	can be stored the difference gives the result that how many variables
	of type of x can be stored in that amount of memory. 
*/

int main()
{
	double x;
	int arr[20];
	int y = MAX2(3, 5);
	int f = MAX3(3, 5, 13);
	
	printf("max(3 ,5) is : %d\n", y); 
	printf("max(3 ,5) is : %d\n", f); 
    printf("double var size: %ld\n", SIZEOF(x));
    printf("double var size: %ld\n", sizeof(x));
    printf("int arr[10] size : %ld\n", SIZEOF(arr));
    printf("int arr[10] size : %ld\n", sizeof(arr));
    printf("double type size: %ld\n", TYPE_SIZEOF(double));
    printf("double type size: %ld\n", sizeof(double));
    
	return (0);
}
