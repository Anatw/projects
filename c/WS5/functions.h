/****************************************************************************
this is the functions headers - it contains all functions headers for this
program.
other files in this program: manager.c, manager.h, functions.c, ws5_ui.c.
this file was written by Anat Wax on February 2020.
****************************************************************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "manager.h"

int compare(char *string, char *input);

int dontcompare(char *string, char *input);

int comparechar(char *string, char *input);

status append(char *input, char *filename);

status addtostart(char *input, char *filename);

status counter(char *input, char *filename);

status exitProgram(char *input, char *filename);

status removefile(char *input, char *filename);

void RemoveFirstChar(char *input);

void error_handling(status exit_status);

#endif
