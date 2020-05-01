#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* execvp(), fork() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */

void catch_sigusr1(int sig_num);

void ChildFun(pid_t parent_pid);
void ParentFun(pid_t child_process);
void InfiniteFork();

int main()
{
    while (1)
    {
        InfiniteFork();
    }

    return (0);
}

void ChildFun(pid_t parent_pid)
{
    char *arg_list[] = {
        "dummy_prog"
        "1",
        "5",
        NULL
    };
    /*pid_t parent_pid = getppid();
    printf("I am a child\n");
    kill(getppid(), SIGUSR1);*/
    wait(&parent_pid);
    printf("I am a child, my pid is %d, my parrent pid is: %d\n", getpid(), getppid());
    execvp("./dummy_prog", arg_list);
    }

void ParentFun(pid_t child_process)
{
    wait(&child_process);
    printf("I am a parent\n");
    kill(child_process, 15);
}

void catch_sigusr1(int sig_num)
{
    signal(SIGUSR1, catch_sigusr1);
    printf("process %d caught signal SIGUSR1\n", sig_num);
}

void InfiniteFork()
{
    pid_t child_process = 0;
    pid_t parent_pid = getpid();
    signal(SIGUSR1, catch_sigusr1);

    child_process = fork();
    if (0 == child_process)
    {
        ChildFun(parent_pid);
    }
    else if (0 < child_process)
    {
        ParentFun(child_process);
    }
    else
    {
        printf("an error in fork!!!");
    }
    
}