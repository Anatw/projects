#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
	char string[] = "an inpusflkjnslkflsknftfwefwefwefewf";
	char *input = string;
	int com = compare("hello", input);
	size_t sizy = strlen(input);
	printf("%zu\n", sizy);

}

int compare(char *string, char *input)
{
	size_t inputlength = (strlen(input) - 1);
	while(*string)
	{
		if (strncmp(string, input, inputlength) == 0) /* two string match */
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
}
