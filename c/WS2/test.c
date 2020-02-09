#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws2_string.h"


int main()
{ 
	char str1[] = "hello world";
	char str2[] = "Hello World";
	/*char str3[] = "hello";
*/	
	char dest[15] = "hi";
	int c = 'o';
	int g = 5;
	int f = 22;

	int *p = &g;
	int *q = &f;
	char *dup;
	char text[] = " text-;with-delimiters  ";
	char text1[] = "   do  ba dooo   ";
	char *token;
	char num1[] = "102";
	char num2[] = "103";
	int *res;
	int i;
	int len;
    

	printf("check Strlen:\n");
	printf("%d\n", Strlen(str1));
	printf("%d\n\n", strlen(str1));

	printf("check Strcpy:\n");
	printf("%s\n", Strcpy(dest, str2));
	printf("%s\n\n", strcpy(dest, str2));

	/*printf("check Strncpy:\n");
	printf("%s\n", Strncpy(dest, str2, 3));
	printf("%s\n\n", strncpy(dest, str2, 3));
*/

	printf("check Strcaseamp:\n");
	printf("%d\n", Strcasecmp(str1, str2));
	
	printf("check Strchr:\n");
	printf("%s\n", Strchr(str1, c));
	printf("%s\n\n", strchr(str1, c));

	/*printf("check Strdup:\n");
	
	dup = Strdup(str1);
	
	printf("%s\n", dup);
	/*printf("%s\n\n", strdup(str1));*/
	/*free(dup);
	*/

	printf("check Strcat:\n");
	printf("%s\n", Strcat(str1, dest));
	printf("%s\n\n", strcat( str1, dest));

	printf("check Strstr:\n");
	printf("%s\n", Strstr(str1,dest));
	printf("%s\n\n", strstr(str1, dest));

	printf("check Strspn:\n");
	printf("%d\n", Strspn(dest, str1));
	printf("%d\n\n", strspn(dest, str1));

	printf("check Strtok:\n");
	token = Strtok(text, "-;");
	while(token != NULL)
	{
		printf("%s\n", token);
		token = Strtok(NULL,";-");
	}

	printf("%d\n", Strspn(dest, str1));
	printf("%ld\n\n", strspn(dest, str1));

	printf("check IsPalindrom:\n");
	printf("%d\n", IsPalindrome(str1));

	printf("check SeveBoom:\n");
	SEVEN_BOOM(g, f);

	printf("\n check SwapPointer:\n");
	printf ("before a = %d b = %d\n", *p, *q);
	swap_pointers_pointers (&p, &q);
	printf ("after a = %d b = %d\n", *p, *q);

	printf("check RmSpaces:\n");
	RmSpaces(text1);
	printf("%s\n", text1);

	printf("check AddTwoStringTogether:\n");
	
    
	printf("%s", add_num(num1, num2));


	
	return 0;
}































