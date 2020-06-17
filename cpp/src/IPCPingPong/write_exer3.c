/*******************************************************************************
IPC - exercise2
Written by Anat Wax, anatwax@gmail.com
Created on: 16.6.20
Reviewer: Shmuel Pablo Sinder
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <unistd.h> /* pipe(), write(), read(), close() */
#include <string.h> /* strlen() */

#include <sys/stat.h> /* mkfifo()*/

#include <unistd.h>
#include <sys/types.h> /* pid_t,  mkfifo() */
#include <sys/wait.h>  /* wait() */
#include <signal.h>    /* sig_atomic_t, kill() */
#include <semaphore.h> /* sem_init(), sem_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>     /* For O_* constants */
#include <stdatomic.h> /* atomic_int */

/*#include "utility.h"*/

#define MASSAGE_SIZE (80)
#define TRUE (1)

int main()
{
    int fd = 0;
    char *current_fifo = "/tmp/myfifo";
    /* Creating the FIFO if it doesn't exist: */
    mkfifo(current_fifo, 0666);
    char array1[MASSAGE_SIZE];
    char array2[MASSAGE_SIZE];

    while (TRUE)
    {
        // Open current_fifo with writing permissions only: */
        fd = open(current_fifo, O_WRONLY);
        // Receieve input from the user */
        fgets(array2, MASSAGE_SIZE, stdin);
        /* write the input into array 2: */
        write(fd, array2, (strlen(array2) + 1));
        close(fd);

        /* Open current_fifo with read only permissions: */
        fd = open(current_fifo, O_RDONLY);

        /* Read from current_info (using fd) into array1: */
        read(fd, array1, sizeof(array1));

        printf("ping: %s\n", array1);
        close(fd);
    }

    return (0);
}
