/****************************************************************
*                                                               *
* functions cheks if palindrom                                  *
*                       	                                    *
****************************************************************/


#include <stdio.h>
#include <string.h>

int Is_Palindrom(const char *str)
{
	int i = 0;
	/* check str length remove 1 since array start from 0*/
	int n = strlen(str) - 1; 
	
	for(i = 0; i < n/2; i++)
	{
		if(str[i] != str[n-i])
		{
			printf("string not palindrom\n");
			return 0;
		}
	}

	printf("string is palindrom\n");
	return 1;
}

int main()
{
	char *str = "tattarsrattat";
	
	int works = Is_Palindrom(str);
	
	printf("%d\n", works);


	return 0;
}
