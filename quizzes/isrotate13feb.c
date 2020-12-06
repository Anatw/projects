#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int isrotate(char *s1, const char *s2);
void rotation(char *s1);

int main()
{
	char s1[] = "12345";
	const char s2[] = "45123";
	/*int s1_length = (int)strlen(s1);*/
	/*int s2_length = (int)strlen(s2);*/
	
	int result = isrotate(s1, s2);
	printf("%d\n", result);
	
	return (0);
	
}

int isrotate(char *s1, const char *s2)
{
	int counter = 0;
	int length = (int)strlen(s1);
	while(counter < length)
	{
		if(strcmp(s1, s2) == 0)
		{
			return (1);
		}
		else
		{
			rotation(s1);
			++counter;
		}
	}
	return (0);
}


void rotation(char *s1)
{
	int index = 0;
	int temp = s1[0];
	int length = (int)strlen(s1);
	for(index = 0; index < (length - 1); ++index)
	{
		*(s1 + index) = *(s1 + index + 1);
	}
	*(s1 + index) = temp;
}
