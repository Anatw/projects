/*******************************************************************************
Write a function which checks the brackets order of a string.
If correct - return 0,
If incorrect - return the index of the first incorrect bracket.
There are 3 types of brackets: {},(), [].

Created: 16.8.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "../ds/include/stack.h"

int CheckBrackets(char* str)
{
    size_t str_len = strlen(str);
    stack_t* open_brackets = StackCreate(str_len);
    size_t i = 0;
    char top_brackets = 0;

    for (i = 0; i < str_len; ++i)
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            StackPush(&str[i], open_brackets);
        }

        if (str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if (StackIsEmpty(open_brackets))
            {
                return ((int)i);
            }

            top_brackets = *(char*)StackPeek(open_brackets);

            if ((str[i] == ')' && top_brackets == '(') ||
                (str[i] == ']' && top_brackets == '[') ||
                (str[i] == '}' && top_brackets == '{'))
            {
                StackPop(open_brackets);
            }
            else
            {
                return ((int)i);
            }
        }
    }

    if (!StackIsEmpty(open_brackets))
    {
        return ((int)i);
    }

    return (0);
}

int main()
{
    char* string1 = ")([4]3*2)";
    char* string2 = "(([4]3*2)";
    char* string3 = "[()]{}{[()()]()}";
    char* string4 = "[()]{]{[()()]()}";

    printf("string1 - %d\n", CheckBrackets(string1));
    printf("string2 - %d\n", CheckBrackets(string2));
    printf("string3 - %d\n", CheckBrackets(string3));
    printf("string4 - %d\n", CheckBrackets(string4));

    return (0);
}
