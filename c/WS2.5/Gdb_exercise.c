#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *Strncpy(char *dest, const char *src, size_t n);

int main()
{
	char s1[] = "WORld!";
	char s2[] = "woRldz!";
	
	
	
	Strncpy(s2, s1, 6);
	printf("\n");
	
	printf("%s\n", s2);
	
	return 0;
}

char *Strncpy(char *dest, const char *src, size_t n)
	{
		int i = 0;
		for (i = 0 ; i <= (int)n && src[i] != '\0' ; i++)	
		{
			*(dest+i) = *(src+i);
		}
		*(dest+i) = '\0';

		while ((n - i) > 0)
		{
			*(dest+i) = '\0';
			i++;
		}
		return dest;
	}

