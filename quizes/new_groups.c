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
#include <sys/wait.h>  /* wait() */
#include <time.h>      /* time, size_t, srand() */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */

int size = 15;
int SumArray(int* group)
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < 15; ++i)
    {
        sum += group[i];
    }

    return (sum);
}

int main()
{
    char* names[] = {
        "Alistair Hudson", "Amir Saraf",          "Anat Wax",
        "Daria Korotkova", "Dean Oron",           "Haim Saadia",
        "Ivanna Fleisher", "Kobi Rappaport",      "Laura Berdah",
        "Lior Cohen",      "Shmuel Pablo Sinder", "Yaacov Evenchik",
        "Yehuda Levavi",   "Yoni Naor",           "Yurii Yashchuk"};

    int group[size];
    int counter = 0;
    int i = 0;

    for (i = 0; i <= size; ++i)
    {
        group[i] = i + 1;
    }

    while (0 != SumArray(group))
    {
        srand(time(NULL));
        i = rand() % 15;

        while (group[i] == 0)
        {
            i = rand() % 15;
        }

        printf("%s\n", names[i]);
        group[i] = 0;
        ++counter;

        if (4 == counter)
        {
            printf("\n");
            counter = 0;
        }
    }

    // for (n = 4; n > 0; --n)
    // {
    //     /* Pick a random index from 0 to i */
    //     j = rand() % (n + 1);

    //     /* Swap arr[i] with the element at random index */
    //     Swap(&names[j], &group[n]);
    // }

    return (0);
}
