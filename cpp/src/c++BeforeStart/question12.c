/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
    #include <stddef.h> /* offsetof(), size_t */
    #include <stdlib.h> /* malloc(), free(), abs(), size_t */
    #include <assert.h> /* assert() */
    #include <time.h> /* time, size_t, srand() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
    #include <stdio.h> /* printf(), size_t */
    #include <string.h> /* size_t, atoi(), memset() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <signal.h>    /* sig_atomic_t, kill() */
    #include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */

int main()
{
    const int i = 0;
    int const a = 1;
    int const* b = &a;
    struct x const x1;

    return (0);
}