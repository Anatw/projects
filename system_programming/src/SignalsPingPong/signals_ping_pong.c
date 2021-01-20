/*******************************************************************************
Signals ping pong

Written by Anat Wax, anatwax@gmail.com
April 30th, 2020
*******************************************************************************/
#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* execvp(), fork() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <string.h> /* memset */

/* #define EXERCISE1 */
/* #define EXERCISE2 */
#define EXERCISE3

sig_atomic_t child_flag = 1; /* SIGUSR1 */
sig_atomic_t parent_flag = 0;   /* SIGUSR2 */

sig_atomic_t unrelated_process_pid = 0;   /* SIGUSR2 */

void SignalHandler(int);
void SecondFuncSignalHandler(int signal, siginfo_t *info, void *param);

#ifdef EXERCISE1
int main()
{
    pid_t child_process = 0;

    struct sigaction action;
    
    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandler;

    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    child_process = fork();

    while (1)
    {
        if (child_process < 0)
        {
            printf("error in fork\n");
            return (1);
        }
        else if (0 == child_process)
        {
            /* this is the child process */
            if (child_flag) /* if flag is ON (1) */
            {
                printf("child, pid: %d\n", getpid());
                child_flag = 0;
                kill(getppid(), SIGUSR2);
            }
        }
        else
        {
            if (parent_flag)
                {
                    /*wait (&child_process);*/
                    printf("parent, pid: %d\n", getpid());
                    parent_flag = 0;
                    kill(child_process, SIGUSR1);
                }
        }
    }
    
    return (0);
}

#endif /* EXERCISE1 */

#ifdef EXERCISE2
int main()
{
    pid_t child_process = 0;
    char *args[] = {"./child_process", NULL};

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandler;
    sigaction(SIGUSR2, &action, NULL);
    
    child_process = fork();

    if (child_process < 0)
    {
        printf("error in fork\n");
        return (1);
    }

    while (1)
    {
        else if (0 == child_process)
        {
            if (child_flag)
            {
                execvp(args[0], args);
            }
        }
        else
        {
            if (parent_flag)
            {
                printf("parent, pid: %d\n", getpid());
                parent_flag = 0;
                kill(child_process, SIGUSR1);
            }
        }
    }
    
    return (0);
}
#endif /* EXERCISE2 */

#ifdef EXERCISE3
int main()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));

    /* this will turn on the flag that enables use in the second function within the sigaction struct: */
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = &SecondFuncSignalHandler;
    /* setting handler for SIGUSR1: */
    sigaction(SIGUSR1, &action, NULL);

    printf("I am the second process (PING). My pid is: %d\n", getpid());
    
    while (1)
    {
        if (parent_flag) /* ping */
        {
            /* first process: */
            printf("The second's process pid (PONG) is %d\n", unrelated_process_pid);
            parent_flag = 0;
            kill(unrelated_process_pid, SIGUSR2);
        }
    }

    return (0);
}
#endif /* EXERCISE3 */

void SignalHandler(int signal)
{
    if (signal == SIGUSR1)
    {
        child_flag = 1;
    }
    else if (signal == SIGUSR2)
    {
        parent_flag = 1;
    }
}

void SecondFuncSignalHandler(int signal, siginfo_t *info, void *param)
{
    (void)param;
    /* switch the flag of the second process (unrelated_process): */
    parent_flag = 1;
    /* si_pid give back the pid of the caller: */
    unrelated_process_pid = info->si_pid;
}