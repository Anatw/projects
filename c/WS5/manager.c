/****************************************************************************
this is the manager.c part - this is the interface is managing the program.
other files in this program: manager.h, functions.c, functions.h. ws5_ui.c.
this file was written by Anat Wax on February 2020.
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "manager.h"
#include "functions.h"

/* the 5th event is the depfault = append to file */
event event_container[5] =
{
	{
		"<",
		comparechar,
		addtostart
	},
	{
		"-count",
		compare,
		counter
	},
	{
		"-exit",
		compare,
		exitProgram
	},
	{
		"-remove",
		compare,
		removefile
	},
	{
		"SUCCESS FOR SURE",
		dontcompare,
		append
	}
};	

status eventCall(char *input, char *filename)
{
	size_t containerSize = (sizeof(event_container) /
						    sizeof(event_container[0]));
	unsigned int index = 0;
	int compareStatus = 0; /* saves exit status of p_compare */
	status operatorStatus = 0; /* saves status of p_operator */
	
	for (index = 0; index < containerSize; ++index)
	{
		char *string = event_container[index].string;
		compareStatus = (*event_container[index].p_compare)(string, input);
		if (compareStatus) /* strings match */
		{
			operatorStatus = (*event_container[index].p_operator)
							  (input, filename);
			break;
		}
	}
	return operatorStatus;
}

void error_handling(status exit_status)
{
	switch (exit_status)
	{
		case FAILURE:
			printf("The requested operation failed\n");
			break;
		
		case EXIT:
			printf("exiting the program\n");
			break;
			
		case FILENOTFOUND:
			printf("The requested file was not found\n");
			break;
	}
}

