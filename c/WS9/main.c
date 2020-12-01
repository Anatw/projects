#include <stdio.h>
#include <string.h>

#include "memLib.h"

int main()
{
	char str1[] = "This is a whole new string and it is now long enough";
	char c = '~';
	char array[100] = {0};
	Memset(str1, c, 20);
	
	printf("%s\n", str1);
	
	return (0);
}
