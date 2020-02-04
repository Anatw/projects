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
