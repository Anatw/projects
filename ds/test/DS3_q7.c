/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#include "stack.h"

// typedef enum Start
// {
//     ( = 0,
//     <,
//     {,
//     [
// } start_t;

int ParenthesesBalance(char *string)
{
}

int main()
{
    char *string1 = "4 + (3 * 4) - {[(5-4) -3 ] * 2}";
    char *string2 = "4 + (3 * 4 - {[(5-4) -3 ] * 2})";

    printf("is balances?: %d\n", ParenthesesBalance(string2));

    return (0);
}
