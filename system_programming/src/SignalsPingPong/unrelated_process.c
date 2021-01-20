#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* execvp(), fork() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <string.h> /* memset */

sig_atomic_t current_process_signal = 0;
sig_atomic_t caller_signal = 0;

void SignalHandler(int signal);

int main()
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = &SignalHandler;

    sigaction(SIGUSR2, &action, NULL);

    current_process_signal = 1;

    printf("unrelated process has started... current process id: %d\n\n", getpid());

    printf("enter a requested process id to start ping-pong with:\n");
    scanf("%d", &caller_signal);

    while (1)
    {
        if (current_process_signal)
        {
            printf("ping\t current process id is %d\n", caller_signal);
            current_process_signal = 0;
            kill(caller_signal, SIGUSR1);
        }
    }

    return (0);
}

void SignalHandler(int signal)
{
    (void)signal;
    current_process_signal = 1;
}
