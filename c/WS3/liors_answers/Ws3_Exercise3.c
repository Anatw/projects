#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_vars(char **environment);
int calculate_strings(char **environment);
void copy_vars(char **envp_p, char **dest, char *strings, int num_of_vars);

/* a function that takes in a charachter string and lowercase it */
char *lower_string(char *str);

int main(int argc, char **argv, char **envp)
{
	int num_of_vars = count_vars(envp);
	int strings_length = calculate_strings(envp);
	
	char **new_envp = (char **)malloc(num_of_vars*sizeof(char *));
	char *strings = (char *)malloc(strings_length*sizeof(char));
	int i = 0;
	
	copy_vars(envp, new_envp, strings, num_of_vars);
	
	for (i = 0; i <+ num_of_vars; i++)
	{
	printf("%d. %s\n", i, new_envp[i]);
	}
	
	printf("There are %d variables\n", num_of_vars);
	printf("We want to allocate %d bytes\n", strings_length);
	return (0);
}

int count_vars(char **environment)
{
	int count = 0;
	for (; *environment != 0; environment++, count++);
	return count;
}

int calculate_strings(char **environment)
{
	int count = 0;
	for (; *environment != 0; environment++)
	{
		count += strlen(*environment) + 1;
	}
	return count;
}

void copy_vars(char **envp_p, char **dest, char *strings, int num_of_vars)
{
	int i = 0;
	
	for (i = 0; i < num_of_vars; i++)
	{
		int string_len = strlen(envp_p[i]);
		strcpy(strings, *(envp_p + i));
		
		lower_string(strings);
		*dest = strings;
		strings += string_len + 1;
		dest++;
	}
}

char *lower_string(char *str)
{
    char *str_start = str;
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
    return str_start;
}
