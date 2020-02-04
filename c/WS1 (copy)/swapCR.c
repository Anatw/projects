#include<stdio.h>



void swap(int *x, int *y);

int main() {

	int a = 2;
	int b = 3;
	int *pa = &a;
	int *pb = &b;
	printf("Before swap:\n");	
	printf("int a = %d, int b = %d \n\n", a, b);

	swap(pa, pb);
	printf("After swap:\n");
	printf("int a = %d, int b = %d \n", a, b);
	return 0;
}

void swap(int *x, int *y) {
	int n = *x;
	*x = *y;
	*y = n;
}


/* why no comments???

line.11-12 we dont have to assign to pointer we can also pass to function with '&' sign before variable name.
swap(&a, &b);

line. 29 please avoid names which are too general like n, you could use "temp".

Nice Job!!
