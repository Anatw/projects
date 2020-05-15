/*******************************************************************************
This is the process of the Watchdog. It uses functions from the "watchdog.c" file.

 gd Watchdog_prog.c -pthread Watchdog.c scheduler.o doubly_linked_list.o uid.o task.o sorted_linked_list.o priority_queue.o -o Watchdog_prog

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#define _XOPEN_SOURCE 700 /* this addes posix to the library - X/Open 7, incorporating POSIX 2008 - to use with the "struct sigaction action;" */
    #include <stdlib.h> /* malloc(), free(), abs(), size_t */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
#include <stdio.h> /* printf(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <sys/types.h> /* pid_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>     /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <signal.h>    /* sig_atomic_t, kill(), sigaction() */

#include "utility.h"
#include "Watchdog.h"
#include "Watchdog_prog.h"
#include "scheduler.h"

/*#define DNDBUG*/

pthread_t dog_thread;
sem_t *is_dog_ready;
scheduler_t *dog_scheduler = NULL;
char *watchdog_args[2];

int main()
{
    /*char program_name[64];
    struct sigaction action;
    watchdog_args[0] = program_name;
    watchdog_args[1] = NULL;
    strcpy(program_name, argv[1]);
    strcat(program_name, " &");*/

printf("3\n");
    #ifndef DNDBUG
    printf("Watchdog_prog.c: main: watchdog process pid: %d\n", getpid());
    printf("Watchdog_prog.c: main: ppid: %d\n", getppid());
    #endif
    
    PostToSem();
    #ifndef DNDBUG
    printf("Watchdog_prog.c: finished PostToSem\n");
    #endif

    /*#ifndef DNDBUG
    printf("Watchdog_prog: creating 'dog_thread'\n");
    #endif
    if (pthread_create(&dog_thread, NULL, &DogSchedInit, watchdog_args))
    {
        #ifndef DNDBUG
        printf("ERROR in pthread_create (producer)\n");
        #endif

        return (1);
    }*/
/*
    #ifndef DNDBUG
    printf("Watchdog_prog: joining the thread 'dog_thread'\n");
    #endif
    pthread_join(dog_thread, NULL);*/
    /* whe user want's to stop the watchdog - he will send a SIGUSR2 to the watchdog, and theo the semaphore, and than sem_e*/

    return (0);
}
/*
void *DogSchedInit(void *watchdog_args)
{*/
 /* pid_t parent_pid = getppid();*/
/*
  #ifndef DNDBUG
  printf("Watchdog_prog: enetered DogSchedInit\n");
  #endif
  dog_scheduler = InitiateScheduler(watchdog_args, &parent_pid);
  #ifndef DNDBUG
  printf("Watchdog_prog.c: I've just initialised my watchdog scheduler:\n");
  #endif

  printf("line 80\n");
  RunSched(dog_scheduler);
  #ifndef DNDBUG
  printf("Watchdog_process.out: I've just ran my scheduler:\n");
  #endif

  return (NULL);
}*/
