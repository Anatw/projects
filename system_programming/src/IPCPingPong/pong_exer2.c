/*******************************************************************************
IPC - exercise2
Written by Anat Wax, anatwax@gmail.com
Created on: 16.6.20
Reviewer: Shmuel Pablo Sinder
*******************************************************************************/
#include <stdio.h>     /* printf(), size_t */
#include <unistd.h>    /* pipe(), write(), read(), close() */
#include <string.h>    /* strlen() */
#include <sys/stat.h>  /* mkfifo()*/
#include <sys/types.h> /* pid_t,  mkfifo() */
#include <fcntl.h>     /* For O_* constants */

#define MASSAGE_SIZE (80) /* 4 chars + '/0' */
#define TRUE (1)

int is_ping = 1;
int is_pong = 0;

int main()
{
    int read_bytes = 0;
    int fd1 = 0;
    char string1[MASSAGE_SIZE];
    char string2[MASSAGE_SIZE];
    char *current_fifo = "/tmp/myfifo";
    /* Creating the FIFO if it doesn't exist: */
    mkfifo(current_fifo, 0666);

    while (TRUE)
    {
        /* Open current_fifo with read only permissions: */
        fd1 = open(current_fifo, O_RDONLY);
        if (0 > fd1)
        {
            return (1);
        }

        /* Read into string 1 the input from user sent into current_buffer: */
        read_bytes = read(fd1, string1, MASSAGE_SIZE);
        string1[read_bytes] = '\0';
        printf("pong: %s\n", string1);
        if (-1 == (close(fd1)))
        {
            return 1;
        }

        /* Open current_fifo in write only mode: */
        fd1 = open(current_fifo, O_WRONLY);
        if (0 > fd1)
        {
            return (1);
        }

        fgets(string2, MASSAGE_SIZE, stdin);
        write(fd1, string2, (strlen(string2) + 1));
        if (-1 == (close(fd1)))
        {
            return 1;
        }
    }

    return (0);
}
