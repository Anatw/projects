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

#endif
