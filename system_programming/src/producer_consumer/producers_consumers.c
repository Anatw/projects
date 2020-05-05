/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
    #include <stddef.h> /* offsetof(), size_t */
    #include <stdlib.h> /* malloc(), free(), abs() */ //* size_t, *//
    #include <assert.h> /* assert() */
    #include <time.h> /* time, size_t, srand() */
    #include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */
    #include <stdio.h> /* printf(), size_t */
    #include <string.h> /* size_t, atoi() */
    #include <sys/types.h> /* pid_t */
    #include <sys/wait.h> /* wait() */
    #include <pthread.h> /* pthread_t, pthread_create() */
Semaphores - posix:
    #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */


#include "utility.h"

/************************* Functions declarations: ****************************/
void ProducerFunc();
void ProducerFunc();

/********************* Glocal variables declarations: *************************/
#define ARRAY_SIZE (1000)
int global_array[ARRAY_SIZE] = {0};

/***************************** Main function: *********************************/

int main()
{   
    pthread_t producer_thread = 0;
    pthread_t consumer_thread = 0;

    while (1)
    {
      if (0 != pthread_create(&producer_thread, NULL, &ProducerFunc, NULL))
      {
        printf("error in pthread_create (producer_thread)\n");
        return (1);
      }

      if (0 != pthread_create(&consumer_thread, NULL, &ConsumerFunc, NULL))
      {
        printf("error in pthread_create (consumer_thread)\n");
        return (1);
      }
    }
    return (0);
}

void ProducerFunc()
{
  int index = 0;
  for (index = 0; index < ARRAY_SIZE; ++index)
  {
    array[index] += 1;
  }
}

void ConsumerFunc()
{
  int index = 0;
  int counetr = 0;
  for (index = 0; index < ARRAY_SIZE; ++index)
  {
    counter += array[index];
  }

  printf("the sum of all the values inside the array id: %d"), counter);
}