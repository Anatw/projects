#include <stdio.h>
#include <string.h>

#include "memLib.h"

int main()
{
	char str1[] = "This is a whole new string";
	char c = 'a';
	char array[] = {c, c};
	
	int i = 0;
	for (i = 0; i < 5; i++)
	printf("%s\n", array);
	
	return (0);
}
