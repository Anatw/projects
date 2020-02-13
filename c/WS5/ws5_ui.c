/****************************************************************************
this is the UI part - this is the interface between the user and the program.
other files in this program: manager.c, manager.h, functions.c, functions.h.
this file was written by Anat Wax on February 2020.
****************************************************************************/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "manager.h"
#include "functions.h"

/* because this main function interact with the user and recieves data from the
user - it must recieve argc and argv */
int main(int argc, char *argv[])
{
	char *filename = NULL;
	int isWorking = 0;
	FILE *filepointer = NULL;
	
	/* '*content' is the pointer to the beggining of the user's string: */
	char *input = NULL;
	/* '*stringLength' is the length of the users string: */
	size_t stringLength = 0;
	/* 'exit_status' is the return status that every function returns. it is
		of enum type 'status': */
	status exit_status = 0; 
	
	/* file naming part: */
	if (argc == 1) /*the user didn't supply any file name */
	{
		filename = "/home/student/git/c/WS5/log.txt";
	}
	else
	{
		filename = argv[1];
	}
	
	/* checking is the new file opens correctly */
	filepointer = fopen(filename, "a+");
	if (!filepointer)
	{
		printf("Error openning the file %s\n", filename);
	}
	fclose(filepointer);
	
	/* recieving input from the user */
	while(exit_status == SUCCESS) /* SUCCESS = 0, FAILURE = 1, EXIT = 2 */
	{
		printf("Enter a string. When you are done, press the enter key\n");
				
		isWorking = getline(&input, &stringLength, stdin);
		
		if (isWorking == (-1))
	    {
    	    printf("No line read\n");
		}
		else
		/* here we send the user's string to the "manager.c" file - to start
		   the isteration between all even_container options */
		{
    		exit_status = eventCall(input, filename);
    	}
    }
	
	error_handling(exit_status);
		
	free(input);
	input = NULL;
	
	return (0);
}
