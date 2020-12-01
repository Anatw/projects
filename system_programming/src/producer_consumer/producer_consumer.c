/*******************************************************************************
Comment and un-comment the defines unser "Exercise sections" to see each phase (one at a time).

                           producer-consumer
                          Written by Anat Wax
                            May 5-6th, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
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


/******** Global variables - EXEC_1_B: **********/
/* is_busy is a sinchronization flag (used by the thread themselfs) - whan it is open (indicated by 0), a thread can enter the critical section, when it is close (indicated by 1) - no thread can enter. */
int is_busy = 0;

/******** Global variables - EXEC_1_C: **********/
atomic_int lock = 0;
#define LOCKED (1)

/******** Global variables - EXEC_1_D: **********/
atomic_int ready_for_producer = 0; /* if this is 1 - the function can run */
atomic_int ready_for_consumer = 0; /* if this is 1 - the function can run */
#define READY (0)
#define DONE (1)

/***************************** Main function: *********************************/
/********** Exercise sections: ************/
/*#define EXCE_1_A*/
/*#define EXCE_1_B*/
/*#define EXCE_1_C*/
#define EXCE_1_D

int main()
{   
    int index = 0;
    pthread_t producer_thread = 0;
    pthread_t consumer_thread = 0;
    
    printf("index address = %p\n", &index);
    printf("consumer_thread = %p\n", &consumer_thread);

    if (0 != pthread_create(&producer_thread, NULL, &ProducerFunc, &index))
    {
        printf("ERROR in pthread_create (producer_thread)\n");
        return (1);
    }

    if (0 != pthread_create(&consumer_thread, NULL, &ConsumerFunc, NULL))
    {
        printf("ERROR in pthread_create (consumer_thread)\n");
        return (1);
    }
    /* pthread_join will stop main from ending before threads ending */
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return (0);
}

/************************** Threads functions: ********************************/
#ifdef EXCE_1_A
void *ProducerFunc(void *index)
{
  while (1)
  {
    for (*(int *)index = 0; *(int *)index < ARRAY_SIZE; ++*(int *)index)
    {
        array[*(int *)index] += 1;
    }
  }
  
  return (NULL);
}

void *ConsumerFunc(void *unused)
{
  int index = 0;
  size_t counter = 0;

  UNUSED(unused);

  while (1)
  {
    counter = 0;
    for (index = 0; index < ARRAY_SIZE; ++index)
    {
        counter += array[index];
    }

    printf("the sum of all the values inside the array id: %ld\n", counter);
  }

  return (NULL);
}
#endif /* EXCE_1_A */


#ifdef EXCE_1_B
void *ProducerFunc(void *index)
{
  while (1)
  {
      if (0 == is_busy)
      {
        is_busy = 1;
        for (*(int *)index = 0; *(int *)index < ARRAY_SIZE; ++*(int *)index)
        {
            array[*(int *)index] += 1;
        }

        is_busy = 0;
      }
  }
  
  return (NULL);
}

void *ConsumerFunc(void *unused)
{
  int index = 0;
  size_t counter = 0;

  UNUSED(unused);
  
  while (1)
  {
      if (0 == is_busy)
      {
        is_busy = 1;
        counter = 0;
        
        for (index = 0; index < ARRAY_SIZE; ++index)
        {
            counter += array[index];
            printf("the sum of all the values inside the array id: %ld\n", counter);
        }

        is_busy = 0;
      }
  }

  return (NULL);
}
#endif /* EXCE_1_B */

#ifdef EXCE_1_C
void *ProducerFunc(void *index)
{
  while (1)
  {
      if (0 == lock)
      {
        __sync_lock_test_and_set(&lock, LOCKED);
        for (*(int *)index = 0; *(int *)index < ARRAY_SIZE; ++*(int *)index)
        {
            array[*(int *)index] += 1;
        }

        __sync_lock_release(&lock);
      }
  }
  
  return (NULL);
}

void *ConsumerFunc(void *unused)
{
  UNUSED(unused);
  int index = 0;
  size_t counter = 0;

  while (1)
  {
      if (0 == lock)
      {
        __sync_lock_test_and_set(&lock, LOCKED);
        counter = 0;

        for (index = 0; index < ARRAY_SIZE; ++index)
        {
            counter += array[index];
        }

        __sync_lock_release(&lock);
      }

    printf("the sum of all the values inside the array id: %ld\n", counter);
  }

  return (NULL);
}
#endif /* EXCE_1_C */

#ifdef EXCE_1_D
void *ProducerFunc(void *index)
{
  while (1)
  {
      if (READY == ready_for_producer)
      {
        __sync_lock_release(&ready_for_consumer);
        for (*(int *)index = 0; *(int *)index < ARRAY_SIZE; ++*(int *)index)
        {
            array[*(int *)index] += 1;
        }
        __sync_lock_test_and_set(&ready_for_producer, DONE);
      }
  }
  
  return (NULL);
}

void *ConsumerFunc(void *unused)
{
  int index = 0;
  size_t counter = 0;

  UNUSED(unused);

  while (1)
  {
      if (READY == ready_for_consumer)
      {
        __sync_lock_release(&ready_for_producer);
        counter = 0;

        for (index = 0; index < ARRAY_SIZE; ++index)
        {
            counter += array[index];
        }

        __sync_lock_test_and_set(&ready_for_consumer, DONE);

        printf("the sum of all the values inside the array id: %ld\n", counter);
      }
  }

  return (NULL);
}
#endif /* EXCE_1_D */
