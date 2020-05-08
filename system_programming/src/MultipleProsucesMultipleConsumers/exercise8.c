/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: Amir Paz
*******************************************************************************/

#include <stdio.h> /* printf(), size_t */

#include <pthread.h> /* pthread_t, pthread_create() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */

#include "utility.h"

#define STRING_SIZE (18)
#define NUM_CONSUMER (8)

/**** Initializing synchronization vraiables: ****/
pthread_cond_t guard;
pthread_mutex_t lock;
sem_t semaphore;
pthread_cond_t condition;

atomic_int massage = 0;
int counter = 0;

void *ProducerFunc(void *unused);
void *ConsumerFunc(void *unused);

int main()
{
    pthread_t producer;
    pthread_t consumer_string[NUM_CONSUMER] = {0};
    int i = 0;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition, NULL);

    sem_init(&semaphore, O_CREAT, 0);
    if (pthread_create(&producer, NULL, &ProducerFunc, NULL))
    {
        printf("ERROR in pthread_create (producer)\n");
        return (1);
    }
    
    for (i = 0; i < NUM_CONSUMER; ++i)
    {
        if (pthread_create(&consumer_string[i], NULL, &ConsumerFunc, NULL))
        {
            printf("ERROR in pthread_create (consumer_string) (in i %d)\n", i);
            return (1);
        }
    }

    pthread_join(producer, NULL);

    for (i = 0; i < NUM_CONSUMER; ++i)
    {
        pthread_join(consumer_string[i], NULL);
    }

    sem_destroy(&semaphore);

    return (0);
}

void *ProducerFunc(void *unused)
{
    UNUSED(unused);

    sem_post(&semaphore);
    pthread_mutex_lock(&lock);
    massage = 4;
    
    /* Enter this while loop only if this is the beggining of the program and no producer thread has executed yet: */
    while (0 == counter)
    {
        printf("Waiting on conditional variable 'guard'\n");
        pthread_cond_wait(&guard, &lock);
    }
    pthread_mutex_unlock(&lock);

    return (NULL);
}

void *ConsumerFunc(void *unused)
{
    UNUSED(unused);
    
    sem_wait(&semaphore);
    ++counter;
    printf("Thread #%d, massage: %d\n", counter, (massage + counter));
    
    if (NUM_CONSUMER == counter)
    {
        pthread_cond_broadcast(&guard);
    }
    sem_post(&semaphore);

    return (NULL);
} 