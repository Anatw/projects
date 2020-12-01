#include <stdio.h>
#include "ws2_string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	const char s1[] = "This is a search able string";
	const char s2[] = "search";
	
	char text[] = "I-;am;text-with;delimiters";
	
	char *token = Strtok(text, "-;");
	char delimit = ' ,-';
	
	/*char s[100], *p, delimit[20]; */
	/*int i=0, len=0; */
	
	
	
	int x = 2;
	int y = 3;
	int *p1 = &x;
	int *p2 = &y;
	
	
	char s[] = "Hello 2 u world!";
	const char s1[] = "WORld!";
	const char s2[] = "woRldz!";
	
	
	
	{
		char *token = Strtok(text, "-;");
		while (token != NULL)
		{
			printf("%s\n", token);
			token = Strtok(NULL, ";-");
		}
	}
	
	
	
	
	printf("%s", Strstr(s1, s2));
	
	printf("\n");
	
	printf("mine: %d\n", Strcasecmp(s1, s2));
	printf("%d\n", Strcasecmp(s1, s2));

	printf("%ld", Strlen(s));
	
	


/********************/

	
	while(len++ != '\0');
	p = strtok(s1,delimit);	
	while(p != NULL)
	{
		printf("%s \n", p);
		p = strtok(NULL, delimit);			
	}


/********************/
	
		
	printf("Before swap: p1: %d, p2: %d\n", *p1, *p2);
	swap_pointers_pointers(&p1, &p2);
	printf("After swap: p1: %d, p2: %d\n", *p1, *p2);
	printf("After swap: x: %d, y: %d\n", x, y);
	
	return 0;


/*int IsPalindrome(const char *str);*/

	const char *palindrom = "!2teret2!";
	printf("%d", (int)IsPalindrome(palindrom));
	
	return 0;
}





