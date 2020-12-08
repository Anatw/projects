/*******************************************************************************
        Multiple producers, Multiple consumers with Atomic Counters
                          Written by Anat Wax
                            May 7th, 2020
                          Reviewer: Amir Paz
*******************************************************************************/

 #include <stdio.h> /* printf(), size_t */
 #include <pthread.h> /* pthread_t, pthread_create() */
 #include <semaphore.h> /* sem_init(), se,_destroy(), sem_wait(), sem_post(), sem_trywait(), sem_getvalue() */
 #include <fcntl.h>           /* For O_* constants */
 #include <stdatomic.h> /* atomic_int */

#include "queue.h"
#include "singly_linked_list.h"

/**** Defining macros: ****/
#define NUM_THREADS (5)
#define BUFFER_SIZE (7)

/**** Initializing synchronization vraiables: ****/
pthread_mutex_t lock;
queue_t *global_queue = NULL;

atomic_int producer_guard = BUFFER_SIZE;
atomic_int consumer_guard = 0;

/**** Declaring threads functions: ****/
void *ProducerFunc(void *data);
void *ConsumerFunc(void *unsued);

int main()
{
    int i = 0;

    pthread_t producer_thread[NUM_THREADS] = {0};
    pthread_t consumer_thread[NUM_THREADS] = {0};

    int data[NUM_THREADS] = {1, 4, 6, 3, 9};

    pthread_mutex_init(&lock, NULL);

    global_queue = QueueCreate();

    if (NULL == global_queue)
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

    QueueDestroy(global_queue);

    return (0);
}

/**** Defining threads functions: ****/

/* works while buffer_size is bigger or equals to zero */
void *ProducerFunc(void *data)
{
    while(1)
    {
        if (BUFFER_SIZE >= producer_guard)
        {
            pthread_mutex_lock(&lock);
            QueueEnqueu(global_queue, data);
            pthread_mutex_unlock(&lock);
            ++consumer_guard;
            --producer_guard;

            printf("data entered: %d\n", *(int *)data);
        }
    }
    
    return (NULL);
}

/************************************/

void *ConsumerFunc(void *unused)
{
    (void)unused;
    
    while(1)
    {
        if (0 < consumer_guard)
        {
            pthread_mutex_lock(&lock);
            QueueDequeu(global_queue);
            pthread_mutex_unlock(&lock);
            --consumer_guard;
            ++producer_guard;

            printf("data dequed\n");
        }
    }

    return (NULL);
}
