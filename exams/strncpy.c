/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

char* Strncpy(char* dest, const char* src, size_t n)
{
    char* dest_begin = dest;

    while (n > 0 && *src != '\0' && *dest != '\0')
    {
        *dest = *src;
        ++dest;
        ++src;
        --n;
    }

    while (n > 0 && *dest != '\0')
    {
        *dest = '\0';
        ++dest;
        --n;
    }

    return (dest_begin);
}

int main()
{
    char dest[] = "morning time";
    char* src = "sleeping";

    /*char dest[] = "sleeping";
    char* src = "morning time";*/

    printf("dest = %s\n", dest);
    Strncpy(dest, src, 20);
    printf("dest = %s\n", dest);

    return (0);
}
