#include <stdio.h>
#include <string.h>


int main()
{
	char array[] = "welcome";
	int p = strlen(array);
	int s = 0;
	int sa = 0;
	printf("%d\n", p);
	s = sizeof(p);
	sa = sizeof(array);
	printf("size of pointer p: %d\n", s);
	printf("size of array: %d\n", sa);
	return 0;
}

