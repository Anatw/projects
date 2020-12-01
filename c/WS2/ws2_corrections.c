#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *Strdup(char source[]); 
char *Strncpy(char *dest, const char *src, size_t n);
size_t Strlen(char *s);

int main()
{ 
	char str1[] = "hello world";
	char str2[] = "Hello World";
	char *dup = 0;
	char dest[15] = "hi";

	printf("check Strdup:\n");
	
	dup = Strdup(str1);
	
	printf("%s\n", dup);
	
	printf("check Strncpy:\n");
	printf("%s\n", Strncpy(dest, str2, 3));
	printf("%s\n\n", strncpy(dest, str2, 3));
		
	return 0;
}


char *Strdup(char source[])
{
	size_t len = Strlen(source);
	char *target = malloc((len + 1) * sizeof(char));
	if(target != 0)
	{
		while (*source)
		{
			*target = *source;
			target++;
			source++;
		}
		*target = '\0';
		return (target - len);
	}
	else
	{
		return 0;
	}
}

char *Strncpy(char *dest, const char *src, size_t n)
{
	int i = 0;
	for (i = 0 ; i <= (int)n && src[i] != '\0' ; i++)	
	{
		*(dest+i) = *(src+i);
	}
	*(dest+i) = '\0';

	return dest;
}



size_t Strlen(char *s)
{
	size_t i = 0;
	while (s[i] != '\0')	
	{
		i++;
	}
	return i;
}

