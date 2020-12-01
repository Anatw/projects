/*******************************************************************************
Recursive stack sorting

Written by Anat Wax, anatwax@gmail.com
Created: 11.8.20
*******************************************************************************/
    #include <stdio.h> /* printf(), size_t */
    #include <stdlib.h> /* malloc(), free(), abs(), size_t */
    #include <assert.h> /* assert() */
    #include <stddef.h> /* offsetof(), size_t */
    #include <time.h> /* time, size_t, srand() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
    #include <string.h> /* size_t, atoi(), memset() */

    #include "../../../ds/include/stack.h"

void InsretSoretd(stack_t* stack, int num)
{
    int temp = 0;

    if (StackIsEmpty(stack) || StackPeek(stack) > num)
    {
        StackPush(stack, num);
        return;
    }

    temp = StackPeek(stack);
    StackPop(stack);

    InsretSoretd(stack, num);

    StachPush(stack, temp);
}

void Sort(stack_t* stack)
{
    int temp = 0;
    if(StackIsEmpty(stack))
    {
        return;
    }

    temp = StackPeek(stack);
    StackPop(stack);

    Sort(stack);

    InsretSoretd(stack,temp);
}
    

int main()
{


    return (0);
}
