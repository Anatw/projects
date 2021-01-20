/*******************************************************************************
Multiple producers, Multiple consumers with FSQ
Written by Anat Wax, anatwax@gmail.com
May 7th, 2020
*******************************************************************************/

#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "producer_consumer_queue.h"
#include "singly_linked_list.h"

/**** Defining macros: ****/
#define NUM_THREADS (5)
#define BUFFER_SIZE (7)

/**** Initializing synchronization vraiables: ****/
pthread_mutex_t lock_producer;
pthread_mutex_t lock_consumer;
circularbuffer_t *global_buffer = NULL;

sem_t producer_sem;
sem_t consumer_sem;

/**** Declaring threads functions: ****/
void *ProducerFunc(void *data);
void *ConsumerFunc(void *unsued);

int main()
{
    int i = 0;

    pthread_t producer_thread[NUM_THREADS] = {0};
    pthread_t consumer_thread[NUM_THREADS] = {0};

    int data[NUM_THREADS] = {1, 4, 6, 3, 9};

    sem_init(&producer_sem, O_CREAT, BUFFER_SIZE);
    sem_init(&consumer_sem, O_CREAT, 0);

    pthread_mutex_init(&lock_producer, NULL);
    pthread_mutex_init(&lock_consumer, NULL);

    global_buffer = CBCreate(BUFFER_SIZE);

    if (NULL == global_buffer)
    {
        printf("ERROR in queue_create");
        return (1);
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_create(&producer_thread[i], NULL, &ProducerFunc, &data[i]))
        {
            printf("ERROR in pthread_create (Producer_thread) (in i %d)\n", i);
            return (1);
        }

        if (0 != pthread_create(&consumer_thread[i], NULL, &ConsumerFunc, NULL))
        {
            printf("ERROR in pthread_create (Consumer_thread) (in i %d)\n", i);
            return (1);
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(producer_thread[i], NULL);
        pthread_join(consumer_thread[i], NULL);
    }

    sem_destroy(&producer_sem);
    sem_destroy(&consumer_sem);

    CBDestroy(global_buffer);

    return (0);
}

/**** Defining threads functions: ****/

void *ProducerFunc(void *data)
{
    /* the semaphore makes sure that the consumer and producer wont collide, and the two different mutexes makes sure that each producer thread and each consumer thread will work one at a time */
    while(1)
    {
        sem_wait(&producer_sem);
        pthread_mutex_lock(&lock_consumer);
        CBWrite(global_buffer, (int *)data);
        pthread_mutex_unlock(&lock_consumer);
       
        sem_post(&consumer_sem);
        printf("data entered: %d\n", *(int *)data);
    }
    
    return (NULL);
}

/************************************/

void *ConsumerFunc(void *unused)
{
    int display = 0;
    (void)unused;
    
    while(1)
    {
        sem_wait(&consumer_sem);
        pthread_mutex_lock(&lock_producer);
        display = CBRead(global_buffer);
        pthread_mutex_unlock(&lock_producer);

        sem_post(&producer_sem);
        printf("data dequed  ========>  %d\n", display);
    }

    return (NULL);
}
