/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#include "stack.h"

void StackInsertion(stack_t* stack, int num)
{
    int temp = 0;
    if (StackIsEmpty(stack) || StackPeek(stack) < num)
    {
        StackPush(stack, num);
        return;
    }

    temp = StackPeek(stack);
    StackPop(stack);

    StackInsertion(stack, num);

    StackPush(stack, temp);
}

void SortStack(stack_t* stack)
{
    int temp = 0;
    if (StackIsEmpty(stack))
    {
        return;
    }

    temp = StackPeek(stack);
    StackPop(stack);

    SortStack(stack);

    StackInsertion(stack, temp);
}

int main()
{

    return (0);
}
