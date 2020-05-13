#include <assert.h> /*assert() */
#include <stdlib.h> /* malloc(), free() */
#include <stdio.h> /* printf() */
#include <ctype.h> /* tolower() */

#include "../../lib/libds.so" /* this is not valid! must connext an h file relevent and add -L to the lib file */

#define NUM (8)

static int foo(int x);
int bar(int x);
void lower_case(char **environ);
static int env_length(char **environ);
void copy_to_buffer(char **environ, char **buffer, int environ_length);
static void print_buffer(char **buffer);

int global_var = 8;
static char *string = "a stringi string";

int main(int argc, char *argv[])
{
	int x = 22;
	int y = 0;
	const float z = 2;
	int *array = malloc(sizeof(int) * NUM);
	int index = 0;
	static int static_number = 0;
	extern char **environ; 	/* environ hold all ENV variables */
	char **buffer = malloc(sizeof(environ) * (4));
	int environ_length = 4;
	
	copy_to_buffer(environ, buffer, environ_length);
	print_buffer(buffer);
	
	printf("\n\n\n\n");
	
	for (index = 1; index < argc; ++index)
	{
		printf("arg[%d] = %s\n", index, argv[index]);
    }
    
	y =	foo(x);
	assert(y == 44);
	
	y = foo(z);
	
	y = bar(x);
	assert(y == 0);
	
	while (index < NUM)
	{
		*(array + index) = x + index;
		++index;
	}
	
	y = foo(global_var);
	assert(y == 16);
	
	for (index = 0; index < NUM; ++index)
	{
		static_number = 9;
		*(array + index) = static_number + index;
	}
	assert(static_number == 9);
	
	printf("string: %s\n", string);
	/**string = 'A';
	printf("string: %s\n", string);*/
	
	free(array);
	free(buffer);
	
	return (0);
}

static int foo(int x)
{
	int y = x * 2;
	
	return (y);
}

int bar(int x)
{
	int y = x - x;
	
	return (y);
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

static int env_length(char **environ)
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

void copy_to_buffer(char **environ, char **buffer, int environ_length)
{
	int cell = 0;
	for(cell = 0; cell < environ_length; cell++)
	{
		*(buffer + cell) = environ[cell];
		printf("hey");
	}
	return;
}

static void print_buffer(char **buffer)
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

