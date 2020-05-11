/*******************************************************************************
        One producer, Many consumers with Condition Variable
                          Written by Anat Wax
                            May 7th, 2020
                          Reviewer: Amir Paz
*******************************************************************************/

#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "utility.h"

/**** Defining macros: ****/
#define STRING_SIZE (18)
#define NUM_CONSUMER (8)

/**** Initializing synchronization vraiables: ****/
pthread_cond_t guard = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock;
sem_t semaphore;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int x = 5;

atomic_int massage = 0;
int counter = 0;

/**** Declaring threads functions: ****/
void *ProducerFunc(void *unused);
void *ConsumerFunc(void *unused);

int main()
{
    pthread_t producer;
    pthread_t consumer_string[NUM_CONSUMER] = {0};
    int i = 0;
    /*sleep (120);*/

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition, NULL);

    printf("producer address: %p\t\n", &producer);
    printf("consumer_string address: %p\t\n", consumer_string);
    printf("i address: %p\t\n", &i);
    printf("guard address: %p\t\n", &guard);
    printf("lock address: %p\t\n", &lock);
    printf("semaphore address: %p\t\n", &semaphore);
    printf("condition address: %p\t\n", &condition);

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

/**** Defining threads functions: ****/

void *ProducerFunc(void *unused)
{
    
    int variables = 0;
    sem_post(&semaphore);
    pthread_mutex_lock(&lock);
    massage = 4;
    UNUSED(unused);

    printf("ProducerFunc - variables address: %p\t\n", &variables);
    printf("ProducerFunc - pthread_mutex_lock address: %p\t\n", &pthread_mutex_lock);
    
    /* Enter this while-loop only if this is the beggining of the program and no producer thread has executed yet: */
    while (0 == counter)
    {
        printf("Waiting on conditional variable 'guard'\n");
        pthread_cond_wait(&guard, &lock);
    }
    pthread_mutex_unlock(&lock);

    return (NULL);
}

/************************************/

void *ConsumerFunc(void *unused)
{
    int variables = 0;
    /* this variable is visibale only inside a thread - TLS area: */
    static pthread_key_t key;
    UNUSED(unused);
    pthread_key_create(&key, NULL);
    
    
    sem_wait(&semaphore);
    ++counter;
    printf("Thread #%d, massage: %d\n", counter, (massage + counter));

 printf("ProducerFunc - (local)variables address: %p\t\n", &variables);
    printf("ConsumerFunc - sem_wait address: %p\t\n", &sem_wait);
    printf("ConsumerFunc - semaphore address: %p\t\n", &semaphore);
    printf("ConsumerFunc - key address: %p\t\n", &key);
 
    
    if (NUM_CONSUMER == counter)
    {
        pthread_cond_broadcast(&guard);
    }
    sem_post(&semaphore);

    return (NULL);
}
