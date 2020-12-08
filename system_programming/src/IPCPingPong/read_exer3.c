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
    char message_receive[MESSAGE_SIZE];
} message_t;

int main()
{
    message_t message;
    int message_id = 0;
    char *current_fifo = "/tmp/myfifo";
    /* ftok convert a pathname and a project identifier to a key: */
    key_t key = ftok(current_fifo, 'a');
    if ((-1) == key)
    {
        return (1);
    }
    printf("Checking messages...\n");

    /* msgget Creates a new message queue: */
    if ((-1) == (message_id = msgget(key, 0666 | IPC_CREAT)))
    {
        return (1);
    }

    /* Receieve the message: */
    if ((-1) == (msgrcv(message_id, &message, MESSAGE_SIZE, 1, 0)))
    {
        return 1;
    }

    printf("Message received: %s\n", message.message_receive);

    /* Send the message: 
    msgsnd(message_id, &message, sizeof(message), 0);*/
    if ((-1) == (msgctl(message_id, IPC_RMID, NULL)))
    {
        return 1;
    }

    return (0);
}
