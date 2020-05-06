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
    #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
    #include <fcntl.h>           /* For O_* constants */
    #include <stdatomic.h> /* atomic_int */


#include "utility.h"

/************************* Functions declarations: ****************************/
void *ProducerFunc(void *index);
void *ConsumerFunc(void *index);

/********************* Global variables declarations: *************************/
#define ARRAY_SIZE (1000)
int array[ARRAY_SIZE] = {0};
size_t counter = 0;

/******** Global variables - EXEC_1_B: **********/
/* is_busy is a sinchronization flag (used by the thread themselfs) - whan it is open (indicated by 0), a thread can enter the critical section, when it is close (indicated by 1) - no thread can enter. */
int is_busy = 0;

/******** Global variables - EXEC_1_C: **********/
atomic_int lock = 0;
#define LOCKED (1)

/***************************** Main function: *********************************/
#define EXCE_1_B
/*#define EXCE_1_C*/

#ifdef EXCE_1_B
int main()
{   
    pthread_t producer_thread = 0;
    pthread_t consumer_thread = 0;
    int index = 0;

    while (counter < 100000)
    {
      if (0 == is_busy)
      {
        is_busy = 1;

        if (0 != pthread_create(&producer_thread, NULL, &ProducerFunc, &index))
        {
          printf("ERROR in pthread_create (producer_thread)\n");
          return (1);
        }

        is_busy = 0;
        /*sleep(1); adding sleep will allow synchronization */
      }
      
      if (0 == is_busy)
      {
        is_busy = 1;

        if (0 != pthread_create(&consumer_thread, NULL, &ConsumerFunc, NULL))
        {
          printf("ERROR in pthread_create (consumer_thread)\n");
          return (1);
        }

        is_busy = 0;
        /*sleep(1); adding sleep will allow synchronization */
      }
    }

    return (0);
}
#endif /* EXCE_1_B */

#ifdef EXCE_1_C
int main()
{   
    pthread_t producer_thread = 0;
    pthread_t consumer_thread = 0;
    int index = 0;
  
    while (counter < 100000)
    {
      if (0 == lock)
      {
        __sync_lock_test_and_set(&lock, LOCKED);

         if (0 != pthread_create(&producer_thread, NULL, &ProducerFunc, &index))
        {
          printf("ERROR in pthread_create (producer_thread)\n");
          return (1);
        }

        __sync_lock_release(&lock);
        /*sleep(1); adding sleep will allow synchronization */
      }
      
      if (0 == lock)
      {
        __sync_lock_test_and_set(&lock, LOCKED);
        if (0 != pthread_create(&consumer_thread, NULL, &ConsumerFunc, NULL))
        {
          printf("ERROR in pthread_create (consumer_thread)\n");
          return (1);
        }

        __sync_lock_release(&lock);
        /*sleep(1); adding sleep will allow synchronization */
      }
    }

    return (0);
}
#endif /* EXCE_1_C */


/************************** Threads functions: ********************************/
void *ProducerFunc(void *index)
{
  for (*(int *)index = 0; *(int *)index < ARRAY_SIZE; ++*(int *)index)
  {
    array[*(int *)index] += 1;
  }
  
  return (NULL);
}

void *ConsumerFunc(void *unused)
{
  UNUSED(unused);
  int index = 0;

  for (index = 0; index < ARRAY_SIZE; ++index)
  {
    counter += array[index];
  }

  printf("the sum of all the values inside the array id: %d\n", counter);
  return (NULL);
}