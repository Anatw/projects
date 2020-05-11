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
    #include <string.h> /* size_t, atoi() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
Semaphores - posix:
    #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */
    #include <stdatomic.h> /* atomic_int */
Semaphores - system v:
    #include <sys/sem.h> /* semaphore: initsem(), semget(), semop(), semctl() */
    #include <sys/ipc.h> /*  */

#include "utility.h"

int main()
{


    return (0);
}