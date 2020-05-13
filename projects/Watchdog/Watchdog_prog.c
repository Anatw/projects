/*******************************************************************************
This is the process of the Watchdog. It uses functions from the "watchdog.c" file.

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
    #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */
    #include <stdatomic.h> /* atomic_int */
#include <signal.h>    /* sig_atomic_t, kill() */

#include "utility.h"
#include "Watchdog.h"
#include "Watchdog_prog.h"
#include "scheduler.h"

#define DNDBUG

int main()
{
    char *program_name = "./Watchdog_prog";
    scheduler_t *dog_scheduler = NULL;
    /* 'O_CREAT | O_EXCL' will create a new semaphore only if it doesn't already exists: */
    sem_t *is_dog_ready = sem_open("dog_sem", O_CREAT | O_EXCL , 0); 
    #ifdef DNDBUG
    printf("Watchdog_process.out: initialising watchdog scheduler:\n");
    #endif
    dog_scheduler = InitiateScheduler(program_name);
    #ifdef DNDBUG
    printf("Watchdog_process.out: initialising watchdog scheduler:\n");
    #endif
    sem_post(is_dog_ready);
    #ifdef DNDBUG
    printf("Watchdog_process.out: initialising watchdog scheduler:\n");
    #endif
    RunSched(dog_scheduler);
    #ifdef DNDBUG
    printf("Watchdog_process.out: initialising watchdog scheduler:\n");
    #endif

/* whe nuse want's to stop the watchdog - he will send a SIGUSR2 to the watchdog, and theo the semaphore, and than 
    sem_e*/


    return (0);
}
