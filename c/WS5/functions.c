#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include "manager.h"
#include "functions.h"


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

/* this is the default function - write the string to the end of the file */
int dontcompare(char *string, char *input)
{
	return (1);
}

int comparechar(char *string, char *input)
{
	if(*string == *input)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

status append(char *input, char *filename)
{
	FILE *filepointer;
	size_t stringLength = strlen(input);
	filepointer = fopen(filename, "a");
	fwrite(input, stringLength, stringLength, filepointer);
	fclose(filepointer);
}

status addtostart(char *input, char *filename)
{
	int fseek(filename, 0, SEEK_SET);
	size_t stringLength = sizeof(input);
	FILE *filepointer;
	filepointer = fopen(filename, "a+");
	if (fseek != 0)
	{
		printf(stderr, "Error : couldn't return to begginning of document\n");
		break;
	}
	
	fwrite(*(input+1), stringLength, stringLength, filename);
	fclose(filename);
}

status counter(char *input, char *filename)
{
	FILE *filepointer;
	int counter = 0;
	char character = 0;
	filepointer = fopen(filename, "a");
		
	for (character = getc(filepointer); character != EOF;
		 character = getc(filepointer))
	{
		if (character == '\n')
		{
			++counter;
		}
		else
		{
			return counter;
		}
	}
}


status exitProgram(char *input, char *filename)
{
	FILE *filepointer;
	filepointer = fopen(filename, "a");
	printf("Exiting the program\n");
	/*fwrite"program was exited by the user"*/
	fclose(filepointer);
	
	exit(0);
}

status removefile(char *input, char *filename)
{
	int status = 0;
	status = remove(filename);
	
	if(status == 0)
	{
		printf("File was deleted succesfully\n");
	}
	else
	{
		 perror("Following error occurred: ");
	}
	exit(0);
}


