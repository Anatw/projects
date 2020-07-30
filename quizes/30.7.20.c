/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h>    /* assert() */
#include <stddef.h>    /* offsetof(), size_t */
#include <stdio.h>     /* printf(), size_t */
#include <stdlib.h>    /* malloc(), free(), abs(), size_t */
#include <string.h>    /* size_t, atoi(), memset() */
#include <sys/types.h> /* pid_t */
#include <time.h>      /* time, size_t, srand() */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */

int FindLCS(char* origin, char* search_inside)
{
    size_t len_org = strlen(origin);
    size_t len_src = strlen(search_inside);

    int i = 0;
    int j = 0;
    int counter = 0;

    while (i < len_org && j < len_src)
    {
        if (origin[i] == search_inside[j])
        {
            ++counter;
            ++i;
        }

        ++j;
    }

    return (counter);
}

int main()
{
    char* str1 = "abcdefg";
    char* str2 = "dfaccbcfgd";

    printf("%d\n", FindLCS(str1, str2));

    return (0);
}
