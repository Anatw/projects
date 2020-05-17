/*******************************************************************************
Program must be in the same folder of the watchdog files supplie

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#define _XOPEN_SOURCE 700 /* this addes posix to the library - X/Open 7, incorporating POSIX 2008 - to use with the "struct sigaction action;" */
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

void __attribute__((constructor)) ThreadCreate();

void *UserInitiateScheduler(void *program_name);
void *WatchdogInitiateScheduler(void *program_name);
void SignalHandler(int signal);
void RunSched(scheduler_t *scheduler);
void *WatchdogSchedulerCreate(void *program_name);
void PostToSem();
void SignalHandlers(int signal);
void RestartProcesses();
int GeneralSendPulse(void *pid);
int GeneralCheckPulse(void *args);
void *InitiateScheduler(char **args, pid_t *pid);


#define DNDBUG

#define SEND_PULSE (1)
#define CHECK_PULSE (5)
/* this flag is made for comunicating with signals: */
sig_atomic_t user_flag = 0;
sig_atomic_t watchdog_flag = 0;
sig_atomic_t global_flag = 0;
/* this stop_scheduler is a flag to stop the watchdog scheduler: */
sig_atomic_t stop_scheduler = 0;
scheduler_t *dog_sched;
sem_t *is_dog_ready;
sem_t *dog_ready;
pid_t watchdog_pid = 0;
pid_t user_pid = 0;
pthread_t thread;
scheduler_t *user_scheduler = NULL;
char *user_program_name;
extern char *__progname;
char string_program_name[64]; /* to accept program name */
char *args[3] = {0};
/* this must be glocal so that the sigaction will be available for all processes: */
struct sigaction action; 


/******************************************************************************/
                          /* Functions definition: */
/******************************************************************************/

void ThreadCreate(int argc, char *argv[])
{
    char user_program_name[64] = {0};
    #ifndef DNDBUG
    printf("Watchdog.c: I'm in WatchdogStart - entered 'WatchdogStart'\n");
    #endif
    args[0] = "./Watchdog_prog";
    args[2] = NULL;
    #ifndef DNDBUG
    printf("Watchdog.c: WatchdogStart: main process pid: %d\n", getpid());
    printf("Watchdog.c: WatchdogStart: ppid: %d\n", getppid());
    #endif
    UNUSED(argc);
    
    /*user_program_name = program_name;*/
    strcpy(user_program_name, argv[0]); /* initializing user's program name */
    strcat(user_program_name, " &");
    args[1] = user_program_name;

    printf("args0: %s\n", args[0]);
    printf("args1: %s\n", args[1]);

    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandlers;
    sigaction(SIGUSR1, &action, NULL);
    /* this is the main process */
    /* launching the thread that will initiate the process scheduler (to watch the watchdog) */
    /* this will move to the constructore function: */
    #ifndef DNDBUG
    printf("constructore: Watchdog.c: user thread created\n");
    #endif
    if (pthread_create(&thread, NULL, &WatchdogSchedulerCreate, NULL)) /* send &thread as argument? */
    {
        #ifndef DNDBUG
        printf("ERROR in pthread_create (producer)\n");
        #endif

        exit (1);
    }

    if (strcmp("Watchdog_prog", __progname) == 0) /* I am in watchdog_prog */
    {
        #ifndef DNDBUG
        printf("Watchdog.c: on Watchdog_prog - joining the thread 'dog_thread'\n");
        #endif
        pthread_join(thread, NULL);
    }
}

/******************************************************************************/

int WatchdogStart(char *program_name)
{
    printf("1\n");
   
    UNUSED(program_name);
    printf("watchdog_pid = %d\n", watchdog_pid);

    if ((watchdog_pid = fork()) == 0) /* Inside Watchdog_prog process */
    {
        printf("2\n");
        #ifndef DNDBUG
        printf("Watchdog.c: watchdog process is launched\n");
        printf("watchdog pid: %d\n\n", getpid());
        #endif
        if (execvp(args[0], args) < 0) /* this will run the exe Watchdog_prog */
        {
            printf("Error in execvp\n");
        }
    }
    else if (0 > watchdog_pid)
    {
        printf("error in fork\n");

        return (1);
    }
    /* else - this is the user process - do nothing... */
    else
    {
        user_pid = getpid();
    }
    
    return (0);
}

/******************************************************************************/


void WatchdogStop()
{
    #ifndef DNDBUG
    printf("Watchdog.c: Stopping watchdog & user schedulers:\n");
    #endif
   /* SchedulerStop(user_scheduler);
    SchedulerDestroy(user_scheduler);

    kill(watchdog_pid, SIGSTOP); - segmentation fault
        
    pthread_join(thread, NULL);*/
}

/******************************************************************************/

void *WatchdogSchedulerCreate(void *program_name)
{
    pid_t *init_process_pid = ((getpid() == user_pid) ?
                                &watchdog_pid : &user_pid);
    #ifndef DNDBUG
    printf("Watchdog.c: entered UserThread:\n");
    #endif
    UNUSED(program_name);
    
    #ifndef DNDBUG
    printf("Watchdog.c: user pid: %d:\n", user_pid);
    #endif
    printf("i'm in WatchdogSchedulerCreate, PID = %d\n", getpid());

    /* Creating a semaphore to act as a flag and wait for the watchdog to signal that it is set and ready. When it is ready the thread watch_watch_dig will start signaling it the "alive" signals: */
    is_dog_ready = sem_open("dog_sem", O_CREAT, 0666, 0);
    #ifndef DNDBUG
    printf("Watchdog: Created the 'is_dog_ready' semaphore\n");
    #endif

    #ifndef DNDBUG
    printf("Watchdog.c: just about to do a sem_wait:\n");
    printf("init_process_pid: %d, watchdog_pid: %d \n\n\n\n\n", *init_process_pid, watchdog_pid);
    #endif
    printf("getpid() = %d\n", getpid());
    printf("init_process_pid = %d\n", *init_process_pid);
    printf("watchdog_pid = %d\n", watchdog_pid);
    printf("user_pid = %d\n", user_pid);
    if (getpid() == user_pid)
    {
        printf("HERE!\n");
    sem_wait(is_dog_ready);
    }

    user_scheduler = InitiateScheduler(args, init_process_pid);
    #ifndef DNDBUG
    printf("##################### current_process_pid = %d #############", *current_process_pid);
    printf("##################### watchdog_pid = %d #############", watchdog_pid);
    printf("##################### getpid() = %d #############", getpid());
    printf("Watchdog.c: I've just initialised my user scheduler:\n");
    #endif

    RunSched(user_scheduler);
    #ifndef DNDBUG
    printf("Watchdog.c: I've just ran my scheduler:\n");
    #endif

    sem_close(is_dog_ready);
    #ifndef DNDBUG
    printf("Watchdog.c: I've just sem_closed the semaphore:\n");
    #endif
    return (NULL);
}

/******************************************************************************/

void RunSched(scheduler_t *scheduler)
{
    int status = SchedulerRun(scheduler);

    #ifndef DNDBUG
    printf("Watchdog.c: in RunSched\n");
    #endif

    if (2 == status)
    {
        printf("ERROR - SchedulerRun - problem in allocation\n");
    }
    
}

/******************************************************************************/

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
        printf("ERROR in sem_post\n");
    }
    #ifndef DNDBUG
    printf("Watchdog.c: I've just did a sem_post:\n");
    #endif
  }
  
/******************************************************************************/

void SignalHandlers(int signal)
{
    UNUSED(signal);
    #ifndef DNDBUG
    printf("Watchdog.c: Got a signal! I am %s, pid: %d - global_flag set to 1\n",__progname, getpid());
    #endif
    global_flag = 1;
}

/******************************************************************************/

int GeneralCheckPulse(void *args)
{
    printf("I am %s, pid: %d\n", __progname, getpid());
    if (1 == global_flag) /* I received an "alive" signal */
    {
        global_flag = 0;
    }
    else
    {
       RestartProcesses(args);
       printf("a.out is done\n");

        return (1);
    }

    return (0);
}

/******************************************************************************/

void RestartProcesses(char **args)
{
    pid_t temp_watchdog_pid = 0;
    #ifndef DNDBUG
    printf("Watchdog.c: CheckPulse: restarting!!!!!!!!! __progname = %s, \n", __progname);
    #endif

    if (strcmp("Watchdog_prog", __progname) == 0) /* I am in watchdog_prog */
    {
        #ifndef DNDBUG
        printf("Watchdog.c: CheckPulse: relaunching user process, current_pid = %d\n", getpid());
        #endif
        /* re-run the users program: */
        stop_scheduler = 1;
        system(args[1]);
        /* send a self kill the same caller proccess = watchdog_prog - because a new watchdog will be created in the new user process: */
        raise(SIGSTOP);
    }
    /* If I'm "a.out" this means watchdog_process has died */
    else /* (strcmp("a.out", __progname) == 0) */
    {
        #ifndef DNDBUG
        printf("Watchdog.c: CheckPulse: sending sigkill to watchdog\n args[0] = %s !!!!!!!!!!!!!!!!!!!!!!!!!\n", args[0]);
        #endif

        is_dog_ready = sem_open("dog_sem", O_EXCL , 0666, 0);
        /* In case the process is still working but for some reason is not sending signals correctly - kill it before re-running it: */
        kill(watchdog_pid, SIGSTOP);
        /* Re-run the watchdog_prog program: */
        /*WatchdogStart(__progname);*/
        if ((temp_watchdog_pid = fork()) == 0)
        {
            printf("New watchdog pid: %d\n", watchdog_pid);
			execvp(args[0], args);
            
        printf("after exec~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }
        else if(-1 == watchdog_pid)
        {
            printf("Couldn't create child\n");
        }
        else /* I'm in the user thread: */
        {
            watchdog_pid = temp_watchdog_pid;
            sem_wait(is_dog_ready);
            
            InitiateScheduler(args, &watchdog_pid);
        }
    }
}

/******************************************************************************/

int GeneralSendPulse(void *pid)
{
    pid_t new_pid = *(pid_t *)pid;
    printf("SendPulse: Sending from: %d to ====> %d\n", getpid(), new_pid);
    /* I am the user */
    #ifndef DNDBUG
    printf("entering GeneralSendPulse\n");
    #endif

    #ifndef DNDBUG
    printf("SendPulse: Sending from: %d to ====> %d\n", getpid(), new_pid);
    #endif
    /*kill(new_pid, SIGUSR1);*/
kill(new_pid, SIGUSR1);
kill(new_pid, SIGUSR1);
   /* if (stop_scheduler)
    {
        #ifndef DNDBUG
        printf("Watchdog.c: SendPulse: stopping dog's scheduler\n");
        #endif
        SchedulerStop(general_sched);
        SchedulerDestroy(general_sched);
    }*/

    return (0);
}

/******************************************************************************/

void *InitiateScheduler(char **args, pid_t *pid)
{
    user_scheduler = SchedulerCreate();
    printf("inside InitiateScheduler - pid = %d\n", getpid());

    /* inserting both tasks: */
    #ifndef DNDBUG
    printf("InitiateScheduler: inserting CheckPulse\n");
    #endif
    SchedulerInsertTask(general_sched, CHECK_PULSE, GeneralCheckPulse, args);
    
    #ifndef DNDBUG
    printf("InitiateScheduler: inserting SendPulse\n");
    #endif
    SchedulerInsertTask(general_sched, SEND_PULSE, GeneralSendPulse, pid);
    
    return (NULL);
}
