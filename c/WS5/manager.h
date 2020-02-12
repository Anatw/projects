#ifndef MANAGER_H
#define MANAGER_H

typedef enum Status	{SUCCESS = 0, FAILURE = 1, EXIT = 2} status; /*this define
"status" as an enum type of status */

status eventCall(char *input, char *filename);

typedef struct Event
{
	char *string;
	int (*p_compare)(char *string, char *input);
	status (*p_operator)(char *input, char *filename);
} event;

#endif
