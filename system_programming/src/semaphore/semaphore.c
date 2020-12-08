/*******************************************************************************
this program create a semaphore using the System V IPC API.

                               Semaphore
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
    #include <stddef.h> /* offsetof(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), system() */ //* size_t, *//
    #include <assert.h> /* assert() */
    #include <time.h> /* time, size_t, srand() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
    #include <stdio.h> /* printf(), size_t */
    #include <string.h> /* size_t, atoi() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <pthread.h> /* pthread_t, pthread_create() */
#include <sys/sem.h> /* semaphore: initsem(), semget(), semop(), semctl() */
#include <sys/ipc.h> /*  */

#include "utility.h"

#define COMMAND_SIZE (2)
#define NUM_OF_THREADS (1)

struct sembuf sops[1];

int main(int argc, char **argv[])
{
    int semid = 0;
    int number = 0; /* variable to store number input from user */
    /* command_latter - variable to store letter-command input from user: */
    char command_latter[COMMAND_SIZE] = {0};
    char *name = "/home/anat/git/anat-wax/system_programming/src/semaphore/semaphore.c";
    key_t key = ftok(name, 'E');

    if (-1 == key)
    {
        printf("ERROR in key\n");
        return (1);
    }
    /* creating the new system v semaphore: */
    semid = semget(key, 1, 0666 | IPC_CREAT);

    sops[0].sem_num = 0;
    sops[0].sem_op = -1;
    sops[0].sem_flg = SEM_UNDO;

    while (0 != strcmp(command_latter, "X"))
    {
        printf("value in semaphore: %d\n", sops[0].sem_num);
        printf("\nYou may change the semaphore using these commands:\n \
            D number - Decrement the value of semaphore by number.\n \
            U number - Increment the value of semaphore by number.\n \
            X - Exit the program.\n");
        scanf("%s %d", command_latter, &number);

        if (0 == strcmp(command_latter, "D"))
        {
            number = number * (-1);
            sops[0].sem_op = -1;
            semop(semid, sops, SEM_UNDO);
            printf("value in semaphore: %d\n", sops[0].sem_num);
        }
        else if (0 == strcmp(command_latter, "U"))
        {
            sops[0].sem_op = 1;
            semop(semid, sops, SEM_UNDO);
            printf("value in semaphore: %d\n", sops[0].sem_num.semval);
        }
        else
        {
            system("clear");
        }
    }
    
    printf("exiting the program...\n");
    return (0);
}