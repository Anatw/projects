#include<stdio.h>

int main()
{
	int d = 8;
	int m = 12;
	int y = 2020;
	int x = (((y << 4) + m) << 5) + d;
	printf("%d\n", x);
	
	d = x % 32;
	m = (x >> 5) % 16;
	y = x >> 9;
	printf("day: %d\n", d);
	printf("month: %d\n", m);
	printf("year: %d\n", y);
	return 0;
}
