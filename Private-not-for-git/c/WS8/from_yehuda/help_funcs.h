#ifndef HELP_FUNCS_H
#define HELP_FUNCS_H

/* recieve num and pointer to an int element, and add num to it  */
void AddToInt(int num, values_union *var);
/* recieve num and pointer to a float element, and add num to it  */
void AddToFloat(int num, values_union *var);
/* recieve num and pointer to a string element, and concatonate num to it  */
void AddToString(int num, values_union *var);

/* recieve pointer to an int element, and print it */
void PrintInt(values_union *var);
/* recieve pointer to a float element, and print it */
void PrintFloat(values_union *var);
/* recieve pointer to a string element, and print it */
void PrintString(values_union *var);

/* empty function for elements that doesn't need clear */
void ClearNothing(values_union *var);
/* recieve pointer to a string element, and clear it with free() */
void ClearString(values_union *var);

/* internal function to get the number of digits in an int */
unsigned int get_int_length(int num);

#endif
