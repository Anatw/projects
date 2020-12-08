#include <stdio.h>  /* printf() */
#include <stdlib.h> /* malloc(), calloc() */
#include <string.h> /* strlen(), strcat() */

#include "primary_funcs.h" /* the main struct defenition is from here */
#include "help_funcs.h"

void AddToInt(int num, values_union *var)
{
    var->int_num += num;
}

void AddToFloat(int num, values_union *var)
{
    var->float_num += (float)num;
}

void AddToString(int num, values_union *var)
{
    /* allocate momery for the buffer that will hold num as a string */
    char *buffer = (char *)malloc((sizeof(char) * get_int_length(num)) + 1);

    if (NULL == buffer)
    {
        printf("can't allocate memory for the string %s\n", var->string);
    }
    else
    {
        unsigned int new_length = 0;

        sprintf(buffer, "%d", num); /* copy the num into a string in buffer */

        /* the length of the strings together: */
        new_length = strlen(var->string) + strlen(buffer) + 1;

        /* reallocate memory for the new concatenated array */
        var->string = realloc(var->string, sizeof(char) *
                                               new_length);

        if (NULL == var->string)
        {
            printf("can't allocate memory for the string %s\n",
                   var->string);
        }
        else
        {
            /* concatenate both of the strings */
            strcat(var->string, buffer);

            free(buffer);
        }
    }
}

void PrintInt(values_union *var)
{
    printf("%d, ", var->int_num);
}
void PrintFloat(values_union *var)
{
    printf("%.3f, ", var->float_num);
}
void PrintString(values_union *var)
{
    printf("%s, ", var->string);
}

void ClearNothing(values_union *var)
{
    ; /* empty function */
}
void ClearString(values_union *var)
{
    free(var->string);
    var->string = NULL;
}

unsigned int get_int_length(int num)
{
    unsigned int count = 0;
    while (num != 0)
    {
        /* Increment digit count */
        count++;

        /* Remove last digit of 'num' */
        num /= 10;
    }

    return (count);
}
