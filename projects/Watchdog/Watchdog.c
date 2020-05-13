/*******************************************************************************
Program must be in the same folder of the watchdog files supplie

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#define _XOPEN_SOURCE 700 /* this addes posix to the library - X/Open 7, incorporating POSIX 2008 */
    #include <stdlib.h> /* malloc(), free(), abs(), size_t */
    #include <assert.h> /* assert() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
#include <stdio.h> /* printf(), size_t */
#include <sys/types.h> /* pid_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */

#include "utility.h"
#include "scheduler.h"
#include "Watchdog.h"

/*#define DNDBUG*/

#define SEND_PULSE (1)
#define CHECK_PULSE (5)
/* this flag is made for comunicating with signals: */
sig_atomic_t flag = 0;
/* this stop_scheduler is a flag to stop the watchdog scheduler: */
sig_atomic_t stop_scheduler = 0;
scheduler_t *dog_sched;
sem_t *is_dog_ready;
pid_t watchdog_pid = 0;
pthread_t watch_watchdog;

int WatchdogStart(char *program_name)
{
    char *args[3] = {0};
    printf("I'm in WatchdogStart\n");
    args[0] = "./Watchdog_prog";
    args[1] = program_name;
    args[2] = NULL;
    /* Creating a semaphore to act as a flag and wait for the watchdog to signal that it is set and ready. When it is ready the thread watch_watch_dig will start signaling it the "alive" signals: */
    is_dog_ready = sem_open("dog_sem", O_CREAT, 0);

    printf("args0: %s\n", args[0]);
    printf("args1: %s\n", args[1]);

    watchdog_pid = fork();
    
    sleep(1);
    if (0 > watchdog_pid)
    {
        #ifndef DNDBUG
        printf("error in fork\n");
        #endif

        return (1);
    }
    else if (0 == watchdog_pid)
    {
        #ifndef DNDBUG
        printf("Watchdog.c: watchdog process is launched\n");
        printf("watchdog pid: %d\n\n", getpid());
        #endif
        execvp(args[0], args); /* this will run the exe Watchdog_prog */
    }
    else
    {
        /* this is the main process */
        /* launching the thread that will initiate the process scheduler (to watch the watchdog) */
        /* this will move to the constructore function: */
        #ifndef DNDBUG
        printf("Watchdog.c: user thread created\n");
        #endif
        if (pthread_create(&watch_watchdog, NULL, &InitiateScheduler, program_name))
        {
            #ifndef DNDBUG
            printf("ERROR in pthread_create (producer)\n");
            #endif

            return (1);
        }
    }

    return (0);
}
/*
void WatchdogStop()
{
    / Stop watchdog scheduler: /
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);
    / Stop user (watch-watchdog) scheduler: /
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);
    
    kill(watchdog_pid, SIGKILL);
        
    pthread_join(&watch_watchdog, NULL)
}*/


void *InitiateScheduler(void *program_name)
{
    dog_sched = SchedulerCreate();

    /* inserting both tasks: */
    #ifndef DNDBUG
    printf("Watchdog.c: inserting CheckPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, CHECK_PULSE, CheckPulse, program_name);
    
    #ifndef DNDBUG
    printf("Watchdog.c: inserting SendPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, SEND_PULSE, SendPulse, dog_sched);
    
    return (dog_sched);
}

void UserSemWait()
{
    sem_wait(is_dog_ready);
}

void RunSched(scheduler_t *scheduler)
{
    int status = SchedulerRun(scheduler);

    #ifndef DNDBUG
    printf("Watchdog.c: in RunSched\n");
    #endif

    #ifndef DNDBUG
    if (2 == status)
    {
        printf("ERROR - SchedulerRun - problem in allocation\n");
    }
    #endif
}


int SendPulse(void *scheduler)
{
    pid_t user_pid = getpid();

    if (watchdog_pid != user_pid)
    {
    #ifndef DNDBUG
    printf("Watchdog.c: SendPulse: user pulse sent\n");
    #endif
        kill(watchdog_pid, SIGUSR1);
    }
    else /* I am the watchdog */
    {
    #ifndef DNDBUG
    printf("Watchdog.c: SendPulse: watchdog sent\n");
    #endif
        kill(getppid(), SIGUSR1);
    }
    
    if (stop_scheduler)
    {
    #ifndef DNDBUG
    printf("Watchdog.c: SendPulse: stopping dog's scheduler\n");
    #endif
        SchedulerStop(scheduler);
        SchedulerDestroy(scheduler);
    }

    return (0);
}

int CheckPulse(void *program_name)
{
    pid_t user_pid = getpid();

    if (1 == flag) /* I received an "alive" signal */
    {
        flag = 0;
    }
    else
    {
        if (watchdog_pid != user_pid)
        {
            #ifndef DNDBUG
            printf("Watchdog.c: CheckPulse: relaunching Watchdog_prog\n");
            #endif
            /* kill and re-run the watchdog - as a child process: */
            stop_scheduler = 1;
            kill(watchdog_pid, SIGKILL);
            WatchdogStart(program_name);
        }
        else /* I am the watchdog process */
        {
            #ifndef DNDBUG
            printf("Watchdog.c: CheckPulse: relaunching user program\n");
            #endif
            /* re-run the user program: */
            execvp(program_name, program_name);
        }

        return (1);
    }

    return (0);
}


void SignalHandler(int signal)
{
    UNUSED(signal);
    flag = 1;
}
