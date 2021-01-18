/*******************************************************************************
Use 'ipcrm -a' to clean memory when done.

IPC - exercise4
Written by Anat Wax, anatwax@gmail.com
Created on: 17.6.20
Reviewer: Shmuel Pablo Sinder
*******************************************************************************/
#include <stdio.h>     /* printf(), size_t */
#include <string.h>    /* memcpy() */
#include <sys/types.h> /* pid_t,  mkfifo(), ftok()*/
#include <sys/ipc.h>   /*  key_t */
#include <sys/shm.h>   /* shmget(), shmat() */

#define MESSAGE_SIZE (80)

int main()
{
    /* ftok generate unique key */
    key_t key = 0;
    char *message = "this is a message sent to you from another process";

    int shmid = 0;

    char *string = NULL;

    key = ftok("my_file", 'a');
    if (-1 == key)
    {
        return 1;
    }

    /* shmget returns an identifier */
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (-1 == shmid)
    {
        return 1;
    }

    /*shmat used to attach to the shared memory */
    string = (char *)shmat(shmid, (void *)0, 0);
    if (NULL == string)
    {
        return 1;
    }

    printf("data inserted to the common queue.\n");
    memcpy(string, message, MESSAGE_SIZE);

    /* Detach from shared memory */
    shmdt(string);

    return 0;
}
