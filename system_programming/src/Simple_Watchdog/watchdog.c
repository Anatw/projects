/*******************************************************************************
Simple Watchdog

Written by Anat Wax, anatwax@gmail.com
April 29th, 2020
*******************************************************************************/
#include <stdlib.h>    /* system() */
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* execvp(), fork() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */

/* #define PhaseOne */
#define PhaseTwo

void ChildFunc();


#ifdef PhaseOne
int main()
{
    pid_t child_proccess = 0;
    int child_pid = 0;
    int i = 1;
    char *args[] = {"./dummy_prog", NULL};

    while (1)
    {
        child_proccess = fork();
        if (0 > child_proccess)
        {
            printf("problem in fork!!\n");
        }
        else if (0 == child_proccess)
        {
            printf("I am a child!\n");
            execvp("./dummy_prog", args); /* this will run the exe dummy_prog */

            break;
        }
        else
        {
            child_pid = wait(&child_proccess);
            printf("child ended, exit status = %d\n", WEXITSTATUS(child_proccess));
        }
    }

    printf("father process (pid: %d) ended (#%d)\n", getpid(), i);
    ++i;
    
    return (0);
}
#endif /* PhaseOne */


#ifdef PhaseTwo
int main()
{
    int counter = 5;

    while (counter > 0)
    {
        printf("say 'who is your daddy?'\nME... one more time...\n\n");
        system("./dummy_prog");
        --counter;
    }
    
    return (0);
}
#endif /* PhaseTwo */