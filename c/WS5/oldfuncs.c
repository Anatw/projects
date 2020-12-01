#include <stdio.h>
#include <stdlib.h>
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

int append(char *input)
{
	int fseek("log.txt", 0, SEEK-END);
	FILE *filepointer;
	fopen("log.txt", "w+");
	fwrite(input, stringLength, stringLength,"log.txt", );
	fclose(log.txt);
}


void addtostart(char *input)
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


/* this function count the numer of lines in the log.txt documwnt */
void counter()
{
	FILE *filepointer;
		if (*filepointer == '\n'
	int counter = 0;
	fopen(log.txt, "r");
	
	while(*filepointer)
	{
		if (*filepointer == '\n')
		{
			++counter;
		}
		else
		{
			++*string;
		}
	}
	fclose(log.txt);
}


enum exit()
{
	
}


void remove()
{
	int status;
	FILE *filepointer;
	fopen(log.txt, "r+");
	status = remove(log.txt);
	
	if(status == 0);
	{
		deleted succesfully
	}
	else
	{
		 perror("Following error occurred: ");
	}
	fclose(log.txt);
}
