/****************************************************************************
functions.c - this file contains all the fuctions for this program.
other files in this program: manager.c, manager.h, functions.h, ws5_ui.c.
this file was written by Anat Wax on February 2020.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include "manager.h"
#include "functions.h"

int compare(char *string, char *input)
{
	size_t inputlength = (strlen(input) - 1);
	
	if (strncmp(string, input, inputlength) == 0) /* two string match */
	{
		return (1);
	}
	else
	{
		return (0);
	}

	return FAILURE;
}

/* this is the default function - write the string to the end of the file */
int dontcompare(char *string, char *input)
{
	string = string; /* added for deleting "unused parameter" warning */
	input = input; /* added for deleting "unused parameter" warning */
	
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
	fwrite(input, stringLength, 1, filepointer);
	
	/* another option: fprintf(filepointer, "%s", input); */
	fclose(filepointer);
	
	return SUCCESS;
}

status addtostart(char *input, char *filename)
{
	char cursor = 0;
	
	FILE *filepointer;
	FILE *fp_temp = NULL;
	
	fp_temp = fopen("/tmp/logtemp.txt", "w+"); /* make temp file */
	
	/* open main file for reading and writing: */
	filepointer = fopen(filename, "r+"); 
	
	/* remove '<' and ' ' from the start of the string: */
	RemoveFirstChar(input);
	
	/* raise error if can't open file */
	if (fp_temp == NULL)
	{
		return (FILENOTFOUND);
	}
	
	/* send to insert regular if fiole dosen't exists yet */
	if (filepointer == NULL)
	{
		return (FAILURE);
	}
	
	/* write the new string to the start of fp_temp */
	fprintf(fp_temp, "%s", input);

	/* locating cursor at the start of fptr */
	cursor = getc(filepointer);
	
	/* copy fptr to fp_temp */
	while (cursor != EOF)
	{
		fputc(cursor, fp_temp); /* copy chracter from fptr to fp_temp */
		cursor = getc(filepointer); /* get cursor to the next char in fptr */
	}
	
	/* get both of the files to the start */
	fseek(filepointer, 0, SEEK_SET);
	fseek(fp_temp, 0, SEEK_SET);
	
	/* locating cursor at the start of fptr */
	cursor = getc(fp_temp);
	
	/* copy fp_temp to fptr */
	while (cursor != EOF)
	{
		fputc(cursor, filepointer); /* copy character from fp_temp to fptr */
		cursor = getc(fp_temp); /* get cursor to the next char in fp_temp */
	}

	fclose(fp_temp);
	fclose(filepointer);

	return (SUCCESS);
}


void RemoveFirstChar(char *input)
{
	char *write = input;

	input += strspn(input, "< ");

	while (*input)
	{
		*write = *input;
		write++;
		input++;
	}
	
	*write = '\0';
}


status counter(char *input, char *filename)
{
	FILE *filepointer;
	int counter = 0;
	char character = 0;
	
	filepointer = fopen(filename, "r+");
	input = input; /* added for deleting "unused parameter" warning */
		
	while((character = getc(filepointer)) != EOF)
	{
		if (character == '\n')
		{
			++counter;
		}
	}
	
	fprintf(filepointer, "This file has %d lines \n", counter);
	printf("The file %s has %d lines\n\n", filename, counter);
	
	fclose(filepointer);
	
	return (SUCCESS);
}


status exitProgram(char *input, char *filename)
{
	input = input; /* added for deleting "unused parameter" warning */
	filename = filename; /* added for deleting "unused parameter" warning */
	
	return (EXIT);
}

status removefile(char *input, char *filename)
{
	int status = 0;
	
	status = remove(filename);
	input = input; /* added for deleting "unused parameter" warning */
	
	if(status == 0)
	{
		printf("File was deleted succesfully\n");
	}
	else
	{
		 perror("Following error occurred: ");
	}
	
	return SUCCESS;
}


