/*******************************************************************************
IPC - exercise1
Written by Anat Wax, anatwax@gmail.com
Created on: 16.6.20
Reviewer: Shmuel Pablo Sinder
*******************************************************************************/
#include <stdio.h>     /* printf(), size_t */
#include <unistd.h>    /* pipe(), write(), read(), close() */
#include <string.h>    /* strlen() */
#include <sys/types.h> /* pid_t */

#define MESSAGE_SIZE (10)
#define TRUE (1)

int is_ping = 1;
int is_pong = 0;

int main()
{
    pid_t pong = 0;
    char receieve_1[MESSAGE_SIZE];
    char receieve_2[MESSAGE_SIZE];
    int pipe1[2]; /* Store beggining and end of pipe1 */
    int pipe2[2]; /* Store beggining and end of pipe2 */
    char *send = "ping";
    char *ret = "pong";

    if (-1 == pipe(pipe1))
    {
        return (1);
    }

    if (-1 == pipe(pipe2))
    {
        return (1);
    }

    if ((pong = fork()) < 0) /* Error */
    {
        return (1);
    }
    while (TRUE)
    {
        if (pong > 0) /* This is the parent (ping) process */
        {
            /* Close the reading end of the first pipe */
            close(pipe1[0]);
            close(pipe2[1]);
            write(pipe1[1], send, strlen(send) + 1); /* Send a ping */

            read(pipe2[0], receieve_1, MESSAGE_SIZE); /* Read massage from pong */
            printf("%s\n", receieve_1);
        }
        else /*(0 == pong) This is the child (pong) process */
        {
            close(pipe2[0]);
            close(pipe1[1]);
            write(pipe2[1], ret, (strlen(ret) + 1));

            read(pipe1[0], receieve_2, MESSAGE_SIZE);
            printf("%s\n", receieve_2);
        }
    }

    return (0);
}
