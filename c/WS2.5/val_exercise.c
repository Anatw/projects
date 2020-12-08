#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Strdup(char source[]);

int main()
{
	char s[] = "Hello 2 u world!";
	
	char *new_string = Strdup(s);
	
	printf("%ld", strlen(s));
	printf("\n");
	
	printf("%s\n", new_string);
	
	free(new_string);
	
	printf("%s\n", new_string);
	
	printf("\n");
	return 0;
}




char *Strdup(char source[])
{
	size_t len = strlen(source);
	char *target = malloc((len + 1) * sizeof(char));
	while (*source)
		{
			*target = *source;
			target++;
			source++;
		}
	*target = '\0';

	return (target - (len));
}

