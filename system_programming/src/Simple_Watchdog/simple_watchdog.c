#include <stdlib.h>
#include <sys/types.h> /* pid_t */
#include <stdio.h> /* printf() */
#include <unistd.h> /* execvp(), fork() */
#include <sys/wait.h> /* wait() */
#include <signal.h> /* sig_atomic_t */

sig_atomic_t child_exit_status = 0;

int SimpleWatchDog();
int Spawn(char *program_name, char **arg_list);

int main ()
{
    SimpleWatchDog();

    return (0);
}

int SimpleWatchDog()
{
    pid_t child_process = 0;
    char *arg_list1[] = {
        "ls", /* the name of the process (argv[0]) */
        "-l",
        NULL};

    child_exit_status = wait(&child_process);
    printf("parent started running...\n");
    Spawn("ls", arg_list1);
       
    if (WIFEXITED(child_process))
    {
        printf("child_process exited noemally with exit code %d\n",
               WEXITSTATUS(child_process));
        
        Spawn("ls", arg_list1);
    }
    else
    {
        printf("child_process exited in an abnormal way!!!\n");
    }

    printf("parent proccess ended... exiting");
    
    return (child_exit_status);
}

int Spawn(char *program_name, char **arg_list)
{
    pid_t child_process = 0;

    if (0 != child_process) /* this is the parent process */
    {
        return (child_process);
    }
    else /* this is the child process */
    {
        printf("hello, i am a child process");
        /* execute the programm. Search for it in the path: */
        execvp(program_name, arg_list);
        
        /* execvp function return ONLY if an error had occured: */
        printf("an error has occured in execpv\n");
        abort();
    }

    return (child_exit_status);
}