/****************************************************************************/
/*						Ya'acov Evenchik									*/
/*			function that takes envp and turns into lower case				*/
/*							10.2.2020										*/
/*																			*/
/****************************************************************************/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int calc_arr(char **env);
int calc_str(char **env);
void copy(char **env_p, char **dest, char *str, int arr_size);
char *to_lower_str(char *str);

int main(int argc, char **argv, char **envp)
{
	int i = 0; /* naming convention - i? */
	int arr_size = calc_arr(envp); /* cells in array */
	int str_length = calc_str(envp); /* chararcter in al cells altogether */
	
	/* type casting malloc to char pointers */
	char **new_envp = (char **)malloc(arr_size * sizeof(char *));
	char *new_str = (char *)malloc(str_length * sizeof(char));
	
	copy(envp, new_envp, new_str, arr_size);
	
	for(i =0; i < arr_size; ++i)
	{
		printf("%s\n", new_envp[i]);
	}
	
	return 0;
}

/* compute the number of envp */
int calc_arr(char **env)
{
	int arr_length = 0;
	
	while(*++env) /* very cool, but hard to read */
	{
		++arr_length;
	}
	
	return arr_length;
}

/*compute the number of characters in all the cells of envpn = one malloc for
all... */
int calc_str(char **env)
{
	int str_size = 0;
	
	while(*++env) /* very cool, but hard to read */
	{
		str_size += (strlen(*env) + 1);
	}
	
	return str_size;
}

void copy(char **env_p, char **dest, char *str, int arr_size)
{
	int i = 0; /* naming convention - i? */
	int new_str_len = 0;
	
	for(i = 0; i < arr_size; ++i)
	{
		new_str_len = strlen(env_p[i]);
		
		strcpy(str, env_p[i]);
		
		to_lower_str(str);
		*dest = str;
		str += (new_str_len + 1);
		++dest;
	}
}

char *to_lower_str(char *str)
{
	char *str_begin = str;
	
	while(*++str)
	{
		*str = tolower(*str);
	}
	
	return str_begin;
}



