#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

/************************************************************************
This program copies all the environment variables in lower case into a new
char** buffer in lower case and prints them.
************************************************************************/

int env_length(char **environ);
void lower_case(char **environ);
void copy_to_buffer(char **environ, char **buffer, int environ_length);
void print_buffer(char **buffer);

int main()
{
	extern char **environ; /*environ hold all ENV variables*/
	/*buffer will later hold a copy of environ. 52 is the number of
	cells in environ. malloc will allocate space on the heap.*/
	char **buffer = malloc(sizeof(environ) * (52));
	int environ_length = env_length(environ);
	printf("length: %d\n\n\n\n", env_length(environ));
	lower_case(environ);
	copy_to_buffer(environ, buffer, environ_length);
	print_buffer(buffer);
		
	return 0;
}

int env_length(char **environ)
{
	int counter = 0;
	int cell = 0;
	while(environ[cell])
	{
		counter++;
		cell++;
	}
	return counter;
}

void lower_case(char **environ)
{
	int cell = 0;
	int cell_char = 0;
	while(environ[cell])
	{
		cell_char = 0;
		while(environ[cell][cell_char])
		{
			environ[cell][cell_char] = \
			tolower(environ[cell][cell_char]);
			cell_char++;
		}
		
		cell++;
	}
	return;
}

void copy_to_buffer(char **environ, char **buffer, int environ_length)
{
	int cell = 0;
	for(cell = 0; cell < environ_length; cell++)
	{
		*(buffer + cell) = environ[cell];
	}
	return;
}

void print_buffer(char **buffer)
{
	int cell = 0;
	cell = 0;
	while(buffer[cell])
	{
		printf("%s\n", buffer[cell]);
		cell++;
	}
	return;
}


/*
int env_char_length(char **environ)
{
	int counter = 0;
	int cell = 0;
	int cell_char = 0;
	while(environ[1])
	{
		cell_char = 0;
		while(environ[cell][1])
		{
		counter++;
		cell++;
		}
	}
	return counter;
}
*/
/****************************************************************************
"env_char_length" functionsould be with moew inverst - chacking the length of
search cell in the array and comparring it to one another, keeping the bidest
of all in memory, and returning it into the second value of the buffer
definition in the main].
****************************************************************************/
