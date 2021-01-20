/*******************************************************************************
One producer, Many consumers with Condition Variable
Written by Anat Wax, anatwax@gmail.com
May 7th, 2020
*******************************************************************************/

#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h> /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "utility.h"

/**** Defining macros: ****/
#define STRING_SIZE (18)
#define NUM_CONSUMER (8)

/**** Initializing synchronization vraiables: ****/
pthread_cond_t guard = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t semaphore;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

atomic_int massage = 0;
atomic_int counter = 0;

/**** Declaring threads functions: ****/
void *ProducerFunc(void *unused);
void *ConsumerFunc(void *unused);

int main()
{
    pthread_t producer;
    pthread_t consumer_string[NUM_CONSUMER] = {0};
    int i = 0;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition, NULL);
    /* Initialized to 1 so that the first thread will be able to open the semaphore */
    sem_init(&semaphore, O_CREAT, 1);

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

    /*pthread_join(producer, NULL); - entering this will create a deadlock eiith the consumer threads */

    for (i = 0; i < NUM_CONSUMER; ++i)
    {
        pthread_join(consumer_string[i], NULL);
    }

    sem_destroy(&semaphore);

    return (0);
}

/**** Defining threads functions: ****/

void *ProducerFunc(void *unused)
{
    UNUSED(unused);

    massage = 4;
    
    /* Enter this while-loop only if this is the beggining of the program and no producer thread has executed yet: */
    while (0 == counter)
    {
        printf("Waiting on conditional variable 'guard'\n");
        pthread_cond_wait(&guard, &lock);
    }

    return (NULL);
}

/************************************/

void *ConsumerFunc(void *unused)
{
    UNUSED(unused);
    
    sem_wait(&semaphore);

    ++counter;

    pthread_mutex_lock(&lock);
    printf("Thread #%d, massage: %d\n", counter, (massage + counter));
    
    if (NUM_CONSUMER == counter)
    {
        pthread_cond_signal(&guard);
        return (NULL);
    }
    pthread_mutex_unlock(&lock);

    sem_post(&semaphore);

    return (NULL);
}
