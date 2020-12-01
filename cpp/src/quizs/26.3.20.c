/*******************************************************************************
Quiz: a. Write 3 different implementations for a function that swaps 2 ints b.
Write a macro that checks whether the system is Big/Little Endian c. Write a
macro that checks if a number is unsigned.

Written by Anat Wax, anatwax@gmail.com
*******************************************************************************/
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <signal.h>  /* sig_atomic_t, kill() */
#include <stddef.h>  /* offsetof(), size_t */
#include <stdio.h>   /* printf(), size_t */
#include <stdlib.h>  /* malloc(), free(), abs(), size_t */
#include <string.h>  /* size_t, atoi(), memset() */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait() */
#include <time.h>      /* time, size_t, srand() */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */

// #define ISUNSIGNED(x)                                                          \
//     ((x - (~x) == 0) ? printf("signed\n") : printf("unsigned\n"))
#define ISUNSIGNED(x)                                                          \
    (((x >= 0) && (~x >= 0)) ? printf("unsigned\n") : printf("signed\n"))
// #define ISUNSIGNED(x)                                                         \
//     (((x - (~x) == 0)) ? printf("positive\n") : printf("negative\n"))

int main()
{
    int x = (9);
    unsigned int y = (9);
    // printf("%d\n", (((x) >= 0) && ((~x) >= 0)));

    printf("(signed) - \n", ISUNSIGNED(x));
    printf("(unsigned) - \n", ISUNSIGNED(y));
    // printf("%d\n", ISUNSIGNED(x));

    return (0);
}
