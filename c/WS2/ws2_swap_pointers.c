#include <stdio.h>
#include <string.h>

/* this function swapps between two pointers to int */


void swap_pointers_pointers(int **pp1, int **pp2);

int main()
{
	int x = 2;
	int y = 3;
	int *p1 = &x;
	int *p2 = &y;
		
	printf("Before swap: p1: %d, p2: %d\n", *p1, *p2);
	swap_pointers_pointers(&p1, &p2);
	printf("After swap: p1: %d, p2: %d\n", *p1, *p2);
	printf("After swap: x: %d, y: %d\n", x, y);
	
	return 0;
}


void swap_pointers_pointers(int **pp1, int **pp2)
{
	int *p = *pp1;
	*pp1 = *pp2;
	*pp2 = p;
}	

