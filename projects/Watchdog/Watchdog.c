/*******************************************************************************
                          Watchdog - test file
                          Written by Anat Wax
                       May 10th - May 16th, 2020
                         Reviewer: Haim Sa'adia
*******************************************************************************/
#define _XOPEN_SOURCE 700 /* this addes posix to the library - X/Open 7, incorporating POSIX 2008 - to use with the "struct sigaction action;" */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */
#include <string.h>    /* memset() */
#include <stdio.h>     /* printf(), size_t */
#include <sys/types.h> /* pid_t */
#include <pthread.h>   /* pthread_t, pthread_create() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <semaphore.h> /* sem_init(), sem_destroy(), sem_wait(), sem_post() */
#include <fcntl.h>     /* For O_* constants */
#include <stdatomic.h> /* atomic_int */

#include "utility.h"
#include "scheduler.h"
#include "Watchdog.h"

void __attribute__((constructor)) ThreadCreate();
void __attribute__((destructor)) ThreadDestroy();

void SignalHandler(int signal);
void RunSched(scheduler_t *scheduler);
void *WatchdogSchedulerCreate(void *program_name);
void PostToSem(char *user_prog_name);
void SignalHandlers(int signal);
void RestartProcesses();
int GeneralSendPulse(void *pid);
int GeneralCheckPulse(void *args);
void *InitiateScheduler(char **args, pid_t *pid);
void FreeMemory();


/*#define DNDBUG*/

#define SEND_PULSE (1)
#define CHECK_PULSE (4)

sig_atomic_t global_flag = 0;
/* this stop_scheduler is a flag to stop the watchdog scheduler: */
sig_atomic_t stop_scheduler = 0;
sem_t *is_dog_ready;
pid_t watchdog_pid = 0;
pid_t user_pid = 0;
pthread_t thread;
scheduler_t *scheduler = NULL;
char *user_program_name;
extern char *__progname;
char *args[3] = {0};
/* this must be glocal so that the sigaction will be available for all processes: */
struct sigaction action;
atomic_int is_watchdog = 0;


/******************************************************************************/
                          /* Functions definition: */
/******************************************************************************/

void ThreadCreate(int argc, char *argv[])
{
    char user_program_name[64] = {0};

    args[0] = "./bin/Watchdog_prog";
    args[1] = argv[0];
    args[2] = NULL;

    UNUSED(argc);
    
    /*user_program_name = program_name;*/
    strcpy(user_program_name, argv[0]); /* initializing user's program name */
    strcat(user_program_name, " &");
    args[1] = user_program_name;

    printf("args0: %s\n", args[0]);
    printf("args1: %s\n\n", args[1]);

    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandlers;
    sigaction(SIGUSR1, &action, NULL);

    /* launching the thread that will initiate the process scheduler (to watch the watchdog) */
    if (pthread_create(&thread, NULL, &WatchdogSchedulerCreate, NULL))
    {
        printf("ERROR in pthread_create (producer)\n");

        exit (1);
    }
}

/******************************************************************************/

int WatchdogStart(char *program_name)
{
    char user_program_name[64] = {0};
    /* initializing user's program name - './a.out' ==> './a.out &': */
    strcpy(user_program_name, program_name); 
    strcat(user_program_name, " &");
    args[1] = user_program_name;

    watchdog_pid = fork();
    if (0 == watchdog_pid) /* Inside Watchdog_prog process */
    {
        if (execv("./bin/Watchdog_prog", args) < 0)
        {
            printf("Error in execvp\n");
        }
    }
    else if (0 > watchdog_pid)
    {
        printf("ERROR in fork\n");

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
    SchedulerStop(scheduler);
    sem_post(is_dog_ready);
    kill(watchdog_pid, SIGINT); /* SIGUSR2 */
    printf("Because I'm dead, I'm dead, you know it...\n");
}

/******************************************************************************/

void *WatchdogSchedulerCreate(void *program_name)
{
    pid_t *init_process_pid = ((getpid() == user_pid) ?
                                &watchdog_pid : &user_pid);
    UNUSED(program_name);

    #ifndef DNDBUG
    printf("I'm in WatchdogSchedulerCreate, PID = %d\n\n", getpid());
    #endif

    /* Creating a semaphore to act as a flag and wait for the watchdog to signal that it is set and ready. When it is ready the thread watch_watch_dig will start signaling it the "alive" signals: */
    is_dog_ready = sem_open("dog_sem", O_CREAT, 0666, 0);
    
    InitiateScheduler(args, init_process_pid);

    /* Id I'm in watchdog_process: */
    if ((strcmp(__progname, "Watchdog_prog")) == 0) 
    {
        SchedulerRun(scheduler);
    }
    else
    {
        while(1)
        {
            sem_wait(is_dog_ready);
            RunSched(scheduler);
        }
    }

    return (NULL);
}

/******************************************************************************/

void RunSched(scheduler_t *scheduler)
{
    int status = SchedulerRun(scheduler);

    if (2 == status)
    {
        printf("ERROR - SchedulerRun - problem in allocation\n");
    } 
}


/******************************************************************************/

void PostToSem(char *user_prog_name)
{
    is_watchdog = 1;
    args[1] = user_prog_name;

    is_dog_ready = sem_open("dog_sem", O_CREAT, 0666, 0);
    
    if (-1 == sem_post(is_dog_ready))
    {
        printf("ERROR in sem_post\n");
    }

    pthread_join(thread, NULL);
}
  
/******************************************************************************/

void SignalHandlers(int signal)
{
    UNUSED(signal);

    global_flag = 1;
}

/******************************************************************************/

int GeneralCheckPulse(void *args)
{
    if (1 == global_flag) /* I received an "alive" signal */
    {
        global_flag = 0;
        #ifndef DNDBUG
        printf("I am pid %d and... I GOT A SIGNAL! WOOHOO\n\n", getpid());
        #endif
    }
    else
    {
        RestartProcesses(args);

        return (1);
    }

    return (0);
}

/******************************************************************************/

void RestartProcesses(char **args)
{
    if (0 == watchdog_pid) /* I am in watchdog_prog */
    {
        /* Killing the users process in case it is just stock and not dead: */
        kill(getppid(), SIGSTOP);
        
        #ifndef DNDBUG
        printf("Restarting %s\n\n", args[1]);
        #endif

        system("./a.out"); /* reloading user process */
        /* Finish the task you are currently running, destroy scheduler, kill yourself - watchdog process: */
        sleep(5);
        FreeMemory();
        abort(); /* Kill ingcurrent process on the spot */
    }
    /* I'm in user proccess - watchdog_process has died: */
    else if (watchdog_pid) 
    {
        kill(watchdog_pid, SIGUSR2);
        WatchdogStop();
        WatchdogStart(args[1]); /* user executable */
    }
}

/******************************************************************************/

int GeneralSendPulse(void *unused)
{
    UNUSED(unused);
  
    /* If i am withing watch_dog prog - user_pid will be equal to 0: */
    if (!user_pid)
    {
        #ifndef DNDBUG
        printf("I am watchdog process, sanding from pid %d to pid %d\n\n", getpid(), getppid());
        #endif

        kill(getppid(), SIGUSR1);
    }
    else if (user_pid) /* I'm in the parrent process */
    {
        #ifndef DNDBUG
        printf("I am user process, sanding from pid %d to pid %d\n\n", user_pid, watchdog_pid);
        #endif

        kill(watchdog_pid, SIGUSR1);
    }

    return (0);
}

/******************************************************************************/

void *InitiateScheduler(char **args, pid_t *pid)
{
    scheduler = SchedulerCreate();

    /* inserting both tasks: */
    SchedulerInsertTask(scheduler, CHECK_PULSE, GeneralCheckPulse, args);
    SchedulerInsertTask(scheduler, SEND_PULSE, GeneralSendPulse, pid);
    
    return (NULL);
}

/******************************************************************************/

void ThreadDestroy()
{
    sem_destroy(is_dog_ready);
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);
}

/******************************************************************************/

void FreeMemory()
{
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);
    sem_destroy(is_dog_ready);
}

/******************************************************************************/
/* Function to dliberatly crash the proocess (segmentation fault) - in order to chack re-initializatiion of processes */
int CrashMyProccess()
{
    char *string = "Crush me";
    char *character = "c";
    return (*string = *character);
}
