/*******************************************************************************
This c file contain function needed to activate and run the watchdog. You must
link your files with the libsched.so - the library of the scheduler with it's
dependencies.
Comment the DNDBUG option to enable debugging prints in the file.

                          Watchdog - test file
                          Written by Anat Wax
                       May 10th - May 16th, 2020
                         Reviewer: Haim Sa'adia
*******************************************************************************/
/* this addes posix to the library - X/Open 7, incorporating POSIX 2008 - to
use with the "struct sigaction action;": */
#define _XOPEN_SOURCE 700
#include <stdio.h>  /* printf(), size_t */
#include <signal.h> /* sig_atomic_t, kill(), sigaction() */
#include <pthread.h>
/* pthread.h is used for: pthread_t, pthread_create(), ptherad_mutex_t,
pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h>
/* semaphore.h is used for: sem_init(), sem_destroy(), sem_wait(), sem_post(),
sem_trywait(), sem_getvalue() */

#include "utility.h"
#include "Watchdog.h"
#include "scheduler.h"

/*************  Function declaration:  *************/
void PostToSem(char *user_prog_name);
void FreeMemory();
int CrashMyProccess();

#define DNDBUG

#ifndef DNDBUG
void *CrashWatchdog(void *unused);
#endif

pthread_t dog_thread;
sem_t *is_dog_ready;
scheduler_t *dog_scheduler = NULL;
char *watchdog_args[2];
struct sigaction dog_action;

/****************  Main thread:  ****************/
int main(int argc, char *argv[])
{
#ifndef DNDBUG
    pthread_t dogdog = 0;
#endif

    watchdog_args[0] = "./Watchdog_prog";
    watchdog_args[1] = argv[1];

    UNUSED(argc);

#ifndef DNDBUG
    pthread_create(&dogdog, NULL, &CrushWatchdog, NULL);
#endif

    PostToSem(watchdog_args[1]);

    return (0);
}

void *CrashWatchdog(void *unused)
{
    UNUSED(unused);
    sleep(3);
    printf("About to crash the watchdog process  %d\n\n", getpid());
    CrashMyProccess();

    return (NULL);
}
