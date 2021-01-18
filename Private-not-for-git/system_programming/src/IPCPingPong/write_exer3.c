/*******************************************************************************
Use 'ipcrm -a' to clean memory when done.

IPC - exercise3
Written by Anat Wax, anatwax@gmail.com
Created on: 16.6.20
Reviewer: Shmuel Pablo Sinder
*******************************************************************************/
#include <stdio.h>     /* printf(), size_t */
#include <sys/stat.h>  /* mkfifo()*/
#include <sys/types.h> /* pid_t,  mkfifo(), ftok()*/
#include <string.h>    /* memcpy() */
#include <sys/ipc.h>   /* key_t */
#include <sys/msg.h>   /* msgget()*/
#include <fcntl.h>     /* For O_* constants */

#define MESSAGE_SIZE (80)

typedef struct Message
{
    long message_type;
    char message_write[MESSAGE_SIZE];
} message_t;

int main()
{
    message_t message;
    int massage_id = 0;
    char *current_fifo = "/tmp/myfifo";
    char *write = "This massage is in curtesy of Anat Wax\n";
    /* ftok convert a pathname and a project identifier to a key: */
    key_t key = ftok(current_fifo, 'a');
    if ((-1) == key)
    {
        return (1);
    }

    /* msgget Creates a new message queue: */
    if ((-1) == (massage_id = msgget(key, 0666 | IPC_CREAT)))
    {
        return (1);
    }

    /* Entring data into message: */
    memcpy(message.message_write, write, MESSAGE_SIZE);
    message.message_type = 1;

    printf("data inserted to the common queue.\n");

    /* Send the message: */
    msgsnd(massage_id, &message, MESSAGE_SIZE, 0);
    ;

    return (0);
}
