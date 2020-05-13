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
#include <string.h> /* memset() */
#include <stdio.h> /* printf(), size_t */
#include <sys/types.h> /* pid_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <errno.h>

#include "utility.h"
#include "scheduler.h"
#include "Watchdog.h"

/*#define DNDBUG*/

#define SEND_PULSE (1)
#define CHECK_PULSE (5)
/* this flag is made for comunicating with signals: */
sig_atomic_t user_flag = 0;
sig_atomic_t watchdog_flag = 0;
/* this stop_scheduler is a flag to stop the watchdog scheduler: */
sig_atomic_t stop_scheduler = 0;
scheduler_t *dog_sched;
sem_t *is_dog_ready;
sem_t *dog_ready;
pid_t watchdog_pid = 0;
pthread_t watch_watchdog;
scheduler_t *user_scheduler = NULL;
char *user_program_name;

void CreateUserThread()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandler;
    sigaction(SIGUSR1, &action, NULL);
    /* this is the main process */
    /* launching the thread that will initiate the process scheduler (to watch the watchdog) */
    /* this will move to the constructore function: */
    #ifndef DNDBUG
    printf("constrocture: Watchdog.c: user thread created\n");
    #endif
    if (pthread_create(&watch_watchdog, NULL, &UserThread, NULL))
    {
        #ifndef DNDBUG
        printf("ERROR in pthread_create (producer)\n");
        #endif

        exit (1);
    }
}


int WatchdogStart(char *program_name)
{
    char *args[3] = {0};
    #ifndef DNDBUG
    printf("Watchdog.c: I'm in WatchdogStart - entered 'WatchdogStart'\n");
    #endif
    args[0] = "./Watchdog_prog";
    args[1] = program_name;
    args[2] = NULL;
    
    user_program_name = program_name;

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

void *UserThread(void *program_name)
{
    #ifdef DNDBUG
    printf("Watchdog.c: entered UserThread:\n");
    #endif
    UNUSED(program_name);

    /* Creating a semaphore to act as a flag and wait for the watchdog to signal that it is set and ready. When it is ready the thread watch_watch_dig will start signaling it the "alive" signals: */
    is_dog_ready = sem_open("dog_sem", O_CREAT, 0666, 0);
    #ifndef DNDBUG
    printf("Watchdog: Created the 'is_dog_ready' semaphore\n");
    #endif

    /*sem_unlink("dog_sem");
    #ifndef DNDBUG
    printf("Watchdog: sem_unlink\n");
    #endif*/
    
    #ifdef DNDBUG
    printf("Watchdog.c: just about to do a sem_wait:\n");
    #endif
    sem_wait(is_dog_ready);
    
    user_scheduler = UserInitiateScheduler(user_program_name);
    #ifdef DNDBUG
    printf("Watchdog.c: I've just initialised my user scheduler:\n");
    #endif

    RunSched(user_scheduler);
    #ifdef DNDBUG
    printf("Watchdog.c: I've just ran my scheduler:\n");
    #endif

    sem_close(is_dog_ready);
    #ifdef DNDBUG
    printf("Watchdog.c: I've just sem_closed the semaphore:\n");
    #endif
    return (NULL);
}

void *UserInitiateScheduler(void *program_name)
{
    dog_sched = SchedulerCreate();

    /* inserting both tasks: */
    #ifndef DNDBUG
    printf("Watchdog.c: inserting UserCheckPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, CHECK_PULSE, UserCheckPulse, program_name);
    
    #ifndef DNDBUG
    printf("Watchdog.c: inserting UserSendPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, SEND_PULSE, UserSendPulse, dog_sched);
    
    return (dog_sched);
}

void *WatchdogInitiateScheduler(void *program_name)
{
    dog_sched = SchedulerCreate();

    /* inserting both tasks: */
    #ifndef DNDBUG
    printf("Watchdog.c: inserting WatchdogCheckPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, CHECK_PULSE, WatchdogCheckPulse, program_name);
    
    #ifndef DNDBUG
    printf("Watchdog.c: inserting WatchdogSendPulse\n");
    #endif
    SchedulerInsertTask(dog_sched, SEND_PULSE, WatchdogSendPulse, dog_sched);
    
    return (dog_sched);
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


int UserSendPulse(void *scheduler)
{
 /* I am the user */
    UNUSED(scheduler);
    user_flag = 1;
    #ifndef DNDBUG
    printf("Watchdog.c: SendPulse: user pulse sent\n");
    #endif
    kill(watchdog_pid, SIGUSR1);

    return (0);
}

int WatchdogSendPulse(void *scheduler)
{
     /* I am the watchdog */
    #ifndef DNDBUG
    printf("Watchdog.c: SendPulse: watchdog sent\n");
    #endif
    kill(getppid(), SIGUSR1);
    
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

/* user check if watchdog process is alive: */
int UserCheckPulse(void *program_name)
{
    if (1 == watchdog_flag) /* I received an "alive" signal */
    {
        watchdog_flag = 0;
    }
    else
    {
        #ifndef DNDBUG
        printf("Watchdog.c: CheckPulse: relaunching Watchdog_prog\n");
        #endif
        /* kill and re-run the watchdog - as a child process: */
        stop_scheduler = 1;
        kill(watchdog_pid, SIGKILL);
        WatchdogStart(program_name);

        return (1);
    }

    return (0);
}

/* watchdog check if user process is alive: */
int WatchdogCheckPulse(void *program_name)
{
    if (1 == user_flag) /* I received an "alive" signal */
    {
        user_flag = 0;
    }
    else
    {
        #ifndef DNDBUG
        printf("Watchdog.c: CheckPulse: relaunching user program\n");
        #endif
        /* re-run the user program: */
        execvp(program_name, program_name);

        return (1);
    }

    return (0);
}


void SignalHandler(int signal)
{
    UNUSED(signal);
    printf("Watchdog.c: SIGUER1 receieved from watchdog\n");
    watchdog_flag = 1;
}


void PostToSem()
  {
    #ifndef DNDBUG
    printf("Watchdog.c: entered PostToSem():\n");
    #endif
    /* 'O_CREAT | O_EXCL' will create a new semaphore only if it doesn't already exists: */
    dog_ready = sem_open("dog_sem", O_EXCL , 0666, 0);
    #ifndef DNDBUG
    printf("Watchdog_prog.c: I've just ran sem_open:\n");
    #endif
    if (NULL == dog_ready)
    {
        printf("ERROR in sem_open (inside 'PostToSem')\n");
        perror("semaphore initilization");
        exit(1);
    }
    printf("280\n");
    if (-1 == sem_post(dog_ready))
    {
        printf("EROOR in sem_post\n");
    }
    #ifndef DNDBUG
    printf("Watchdog.c: I've just did a sem_post:\n");
    #endif
  }
  