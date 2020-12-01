/*****************************************************************************
* File Name: fixed_size_queue.c												 *
* Writer: Lior Cohen														 *
* Date: 10/05/2020														     *
* Purpose: The fucntions file for the fixed size queue data structure		 *
* Code reviewer: Yehuda Levavi											 	 *
******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */

#include "fixed_size_queue.h"

/* #define SIZE */


struct fixed_size_queue
{
	size_t read;
    size_t write;
    size_t capacity;
    #ifdef SIZE
    size_t size;
    #endif /* SIZE */
    int *container;
};

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/



/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/

fsq_t *FSQCreate(size_t capacity)
{
    fsq_t *new_queue = (fsq_t *)malloc(sizeof(fsq_t));

    if (NULL == new_queue)
    {
        return (NULL);
    }

    new_queue->container = (int *)malloc(sizeof(int) * capacity);

    if (NULL == new_queue->container)
    {
        free(new_queue);
        new_queue = NULL;

        return (NULL);
    }

    new_queue->read = 0;
    new_queue->write = 0;
    
    #ifdef SIZE
    new_queue->size = 0;
    #endif /* SIZE */

    new_queue->capacity = capacity;

    return (new_queue);
}


void FSQDestroy(fsq_t *queue)
{
    free(queue->container);
    queue-> container = NULL;

    free(queue);
    queue = NULL;
}

int FSQEnqueue(fsq_t *queue, int data)
{
    assert(queue);

    /*if (queue->size == queue->capacity)
    {
        return (1);
    }*/

    queue->container[queue->write] = data;
    queue->write = (queue->write + 1) % queue->capacity;

    #ifdef SIZE
    queue->size += 1;
    #endif /* SIZE */

    return (0);
}

int FSQDequeue(fsq_t *queue)
{
    assert(queue);

    /*if (FSQIsEmpty(queue))
    {
        return (1);
    }*/

    queue->read = (queue->read + 1) % queue->capacity;

    #ifdef SIZE
    queue->size -= 1;
    #endif /* SIZE */

    return (0);
}

int FSQPeek(fsq_t *queue)
{
    assert(queue);

    return (queue->container[queue->read]);
}

#ifdef SIZE
size_t FSQSize(fsq_t *queue)
{
    assert(queue);

    return (queue->size);
}

int FSQIsEmpty(fsq_t *queue)
{
    assert(queue);

    return (FSQSize(queue) == 0);
}
#endif /* SIZE */