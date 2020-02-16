/****************************************************************************
this is the manager part header - this is the interface managing the program.
other files in this program: manager.c, functions.c, functions.h. ws5_ui.c.
this file was written by Anat Wax on February 2020.
****************************************************************************/

#ifndef MANAGER_H
#define MANAGER_H

/* this define "status" as an enum type of status: */
typedef enum Status	{SUCCESS = 0, FAILURE = 1, EXIT = 2,
					 FILENOTFOUND = 3} status;

status eventCall(char *input, char *filename);

typedef struct Event
{
	char *string;
	int (*p_compare)(char *string, char *input);
	status (*p_operator)(char *input, char *filename);
} event;

#endif
