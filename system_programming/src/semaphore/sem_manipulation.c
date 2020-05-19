/*******************************************************************************
This program create a semaphore using the Possix API.
Please note, is you decrease the value in the samaphore belloe it's capacity (INIT_VALUE), it will get into "eait" condition and the programm will be frozen on this condition (you must use cntl + C to terminate the program and start an etirely new semaphore under a new semaphore name).

                               Semaphore
                          Written by Anat Wax
                            May 4th, 2020
                          Reviewer: Amir Saraf
*******************************************************************************/

#include <stdio.h>      /* printf() */
#include <string.h>     /* memset() */
#include <semaphore.h>	/* sem functions */
#include <sys/stat.h>	/* S_IRWXU */
#include <fcntl.h>		/* sem functions, O_CREAT */
#include <stdlib.h>     /* system() */

#define INIT_VALUE (100)
#define WORD_SIZE (10)


int main(int argc, char *argv[])
{
	sem_t *main_sem = NULL;
	char *sem_name = argv[1];
	
	int sem_value = 0;
	int difference = 0;
	/* User command letter will be scanf to here: */
	char command_latter[WORD_SIZE] = {0};
	/* user entered number will be scanf to here" */
	int number = 0;
	/* inisializing the new samphore: */
	main_sem = sem_open(sem_name, O_CREAT, S_IRWXU, INIT_VALUE);

    while (0 != strcmp(command_latter, "X"))
    {
		sem_getvalue(main_sem, &sem_value);
		system("clear");
		printf("The semaphore value right now is %d\n", sem_value);
        printf("\nYou may change the semaphore using these commands:\n \
            D - Decrement the value of semaphore.\n \
            U - Increment the value of semaphore.\n \
            X - Exit the program.\n");
        scanf("%s", command_latter);

		/* Decreasing the semaphore */
		if (0 == strcmp(command_latter, "D") ||
			0 == strcmp(command_latter, "d"))
		{
			printf("Enter the amount to decrease up to %d\n", sem_value);
			scanf("%d", &number);

			while (0 != number)
			{
				sem_wait(main_sem);
				--number;
			}
		}
		/* Increasing the semaphore */
		else if (0 == strcmp(command_latter, "U") ||
				 0 == strcmp(command_latter, "u"))
		{
			difference = INIT_VALUE - sem_value;
			printf("Enter the amount to increase up to %d\n", difference);
			scanf("%d", &number);

			while (0 != number)
			{
				sem_post(main_sem);
				--number;
			}
		}
	}
	/* Wehn exiting the program, these functions will set the semaphore back to it's intial position: */
	sem_close(main_sem);
	sem_unlink(sem_name);

	return (0);
}
