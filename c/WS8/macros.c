/*******************************************************************************
					  	 Written by Anat Wax
						  February 18, 2020
						Reviewer: Lusy Volkov
*******************************************************************************/

#include <stdio.h> /* printf() */

#define MAX2(a, b) ((a > b) ? a : b)

/* if c is greater than a or b - return c, else - find who is bigger - a or b */
#define MAX3(a, b, c) ((MAX2(a, b) > c) ? (MAX2(a, b)) : c)

/*the next memory address minus the VAR memory address will give the VAR size*/
#define SIZEOF_VAR(VAR) ((size_t)(&VAR + 1) - (size_t)(&VAR))


#define SIZEOF_TYPE(TYPE) (((size_t)(1 + ((TYPE *)0))) - ((size_t)((TYPE *)0)))


int main()
{
	char x = 3;
	double z;
	int arr[20];
	int y = MAX2(3, 5);
	int f = MAX3(3, 65, 15);
	
	printf("%ld\n", SIZEOF_VAR(x));
	printf("max(3 ,5) is : %d\n", y); 
	printf("max(3 ,65, 15) is : %d\n", f); 
    printf("double var size: %ld\n", SIZEOF_VAR(z));
    printf("double var size: %ld\n", sizeof(z));
    printf("int arr[10] size : %ld\n", SIZEOF_VAR(arr));
    printf("int arr[10] size : %ld\n", sizeof(arr));
    printf("double type size: %ld\n", SIZEOF_TYPE(double));
    printf("double type size: %ld\n", sizeof(double));
    
	return (0);
}

