#include <stdio.h>
#include <stdlib.h> /* system() */

#include "mine.h"

int main()
{
	int num = 0;
	char str[1] = {0};
	
	system("clear");
	printf("\n");
	
	printf("Think of a number between 1 and 100\n");
	printf("But be carefull - you have to do calculations so, choose wisely :)\n");
	printf("\nPress Enter when you have one, don't tell me what it is\n");
	fgets(str, 2, stdin);
	
	ThinkOfaNum(num);
	
	return (0);
}
