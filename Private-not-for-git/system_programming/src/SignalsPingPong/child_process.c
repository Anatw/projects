#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* execvp(), fork() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <string.h> /* memset */

sig_atomic_t child_flag = 0;

void SignalHandler(int signal);

int main()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandler;
    sigaction(SIGUSR1, &action, NULL);

    child_flag = 1;

    while (1)
    {
        if (child_flag)
        {
            printf("Hello! I'm a child process!!\n pid: %d\n", getpid());
            child_flag = 0;
            kill(getppid(), SIGUSR2);
        }
    }

    return (0);
}

void SignalHandler(int signal)
{
    (void)signal;
    child_flag = 1;
}