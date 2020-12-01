/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

        Multiple producers, Multiple consumers - exercises 1-3
                          Written by Anat Wax
                            May 6-7th, 2020
                          Reviewer: Amir Paz 
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
#include <fcntl.h>           /* For O_* constants */
#include <stdatomic.h> /* atomic_int */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "queue.h"
#include "singly_linked_list.h"

/*#define EX1*/
#define EX2
/*#define EX3*/

/**** Defining macros: ****/
#define NUM_THREADS (5)
#define BUFFER_SIZE (7)

/**** Initializing synchronization vraiables: ****/
pthread_mutex_t lock;
queue_t *global_queue = NULL;
circularbuffer_t *global_buffer = NULL;
#ifdef EX2
sem_t semaphore;
#endif /*EX2*/

#ifdef EX3
sem_t produer_sem;
sem_t consumer_sem;
#endif /*EX3*/

/**** Declaring threads functions: ****/
void *ProducerFunc(void *data);
void *ConsumerFunc(void *unsued);

int main()
{
    int i = 0;

    pthread_t producer_thread[NUM_THREADS] = {0};
    pthread_t consumer_thread[NUM_THREADS] = {0};

    int data[NUM_THREADS] = {1, 4, 6, 3, 9};
    
    #ifdef EX2
    sem_init(&semaphore, O_CREAT, 0);
    #endif /*EX2*/
    
    #ifdef EX3
    sem_init(&produer_sem, O_CREAT, BUFFER_SIZE);
    sem_init(&consumer_sem, O_CREAT, 0);
    #endif /*EX3*/

    pthread_mutex_init(&lock, NULL);

    #ifdef EX2
    global_queue = QueueCreate();
    #endif /*EX2*/

    #ifdef EX3
    global_buffer = CBCreate(BUFFER_SIZE);
    #endif /*EX3*/
    
    if (NULL == global_queue)
    {
        printf("ERROR in queue_create");
        return (1);
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_create(&producer_thread[i], NULL, &ProducerFunc, &data[i]))
        {
            printf("ERROR in pthread_create (producer_thread) (in i %d)\n", i);
            return (1);
        }

        if (0 != pthread_create(&consumer_thread[i], NULL, &ConsumerFunc, NULL))
        {
            printf("ERROR in pthread_create (producer_thread) (in i %d)\n", i);
            return (1);
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(producer_thread[i], NULL);
        pthread_join(consumer_thread[i], NULL);
    }

    #ifdef EX2
    sem_destroy(&semaphore);
    #endif /*EX2*/

    #ifdef EX3
    CBDestroy(global_buffer);
    #endif /*EX3*/

    QueueDestroy(global_queue);

    return (0);
}

/**** Defining threads functions: ****/
/**** Exercise 1: ****/
#ifdef EX1

void *ProducerFunc(void *data)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        QueueEnqueu(global_queue, data);
        pthread_mutex_unlock(&lock);
        printf("data entered: %d\n", *(int *)data);
    }
    
    return (NULL);
}

/**************************/

void *ConsumerFunc(void *unused)
{
    (void)unused;

    while(1)
    {
        pthread_mutex_lock(&lock);
        QueueDequeu(global_queue);
        pthread_mutex_unlock(&lock);
        printf("data dequed\n");
    }

    return (NULL);
}

#endif /*EX1*/

/**** Exercise 2: ****/
#ifdef EX2

void *ProducerFunc(void *data)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        QueueEnqueu(global_queue, data);
        sem_post(&semaphore);
        pthread_mutex_unlock(&lock);
       
        printf("data entered: %d\n", *(int *)data);
    }
    
    return (NULL);
}

/**************************/

void *ConsumerFunc(void *unused)
{
    (void)unused;
    
    while(1)
    {
        sem_wait(&semaphore);
        pthread_mutex_lock(&lock);
        QueueDequeu(global_queue);
        pthread_mutex_unlock(&lock);

        printf("data dequed\n");
    }

    return (NULL);
}

#endif /*EX2*/

/**** Exercise 3: ****/
#ifdef EX3

void *ProducerFunc(void *data)
{
    sem_post(&semaphore);
    
    while (1)
    {
        pthread_mutex_lock(&lock);
        CBWrite(global_buffer, data);
        pthread_mutex_unlock(&lock);
       
        printf("data entered: %d\n", *(int *)data);
    }
    
    return (NULL);
}

/**************************/

void *ConsumerFunc(void *unused)
{
    (void)unused;
    
    sem_wait(&semaphore);

    while(1)
    {
        pthread_mutex_lock(&lock);
        QueueDequeu(global_queue);
        pthread_mutex_unlock(&lock);

        printf("data dequed\n");
    }

    return (NULL);
}

#endif /*EX3*/
