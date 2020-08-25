/*******************************************************************************
A. implement a function that receives a double and returns its square root.

B. implement a queue with two stacks.
support Enqueue, Dequeue, size.

Written by Anat Wax, anatwax@gmail.com
Created: 23.8.20
*******************************************************************************/
#include <errno.h>
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#include "stack.h"

double SqareRoot(double number)
{
    double mid_range = number / 2;
    double top = number;
    double buttom = 0;
    double result = (mid_range * mid_range);

    while (!((number >= result - 0.1) && (number <= (result + 0.1))))
    {
        if (result > number)
        {
            top = mid_range;
            mid_range /= 2;
        }
        else
        {
            buttom = mid_range;
            mid_range = (buttom + top) / 2;
        }

        result = (mid_range * mid_range);
    }

    return (mid_range);
}

void PartA()
{
    double number = 90215;
    printf("SquareRoot of %f is %f\n", number, SqareRoot(number));
}

/*////////////////////////////////////////////////////////////////////////////*/

typedef struct Queue
{
    stack_t* stack_a;
    stack_t* stack_b;
    size_t m_capacity;
    int main_stack;
} t_queue;

size_t QueueSize(t_queue* queue)
{
    size_t size = 0;
    size = StackSize(queue->stack_a);
    size += StackSize(queue->stack_b);

    return (size);
}

int QueueEnqueue(t_queue* queue, void* data)
{
    if (StackSize(queue->stack_a) < queue->m_capacity)
    {
        StackPush(data, queue->stack_a);

        return (0);
    }

    perror("Queue reached it's maximum capacity");
    return (1);
}

int QueueDeque(t_queue* queue)
{
    int return_value = 0;
    if (StackIsEmpty(queue->stack_b))
    {
        while (!StackIsEmpty(queue->stack_a))
        {
            StackPush(StackPeek(queue->stack_a), queue->stack_b);
            StackPop(queue->stack_a);
        }
    }

    return_value = *(int*)StackPeek(queue->stack_b);
    StackPop(queue->stack_b);

    return (return_value);
}

void PartB()
{
    t_queue* queue = (t_queue*)malloc(sizeof(queue));
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int data7 = 7;

    queue->m_capacity = 100;
    queue->stack_a = StackCreate(queue->m_capacity);
    queue->stack_b = StackCreate(queue->m_capacity);

    printf("queue size is %ld\n", QueueSize(queue));

    QueueEnqueue(queue, &data1);
    QueueEnqueue(queue, &data2);
    QueueEnqueue(queue, &data3);
    printf("Item dequeued from stack: %d\n", QueueDeque(queue));
    QueueEnqueue(queue, &data4);
    QueueEnqueue(queue, &data5);

    printf("queue size is %ld\n\n", QueueSize(queue));

    printf("Item dequeued from stack: %d\n", QueueDeque(queue));

    printf("queue size is %ld\n\n", QueueSize(queue));

    QueueEnqueue(queue, &data6);
    printf("Item dequeued from stack: %d\n", QueueDeque(queue));
    printf("Item dequeued from stack: %d\n", QueueDeque(queue));
    printf("Item dequeued from stack: %d\n", QueueDeque(queue));

    QueueEnqueue(queue, &data7);

    QueueEnqueue(queue, &data1);
    QueueEnqueue(queue, &data2);
    QueueEnqueue(queue, &data3);

    printf("queue size is %ld\n\n", QueueSize(queue));

    while (QueueSize(queue) != 0)
    {
        printf("Item dequeued from stack: %d\n", QueueDeque(queue));
    }

    printf("queue size is %ld\n\n", QueueSize(queue));
}

int main()
{
    /*PartA();*/

    PartB();

    return (0);
}
