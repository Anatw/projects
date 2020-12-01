/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "utility.h"
#include "heap.h"
#include "dynamic_vector.h"

#define VECTOR_SIZE (5)
#define ZERO (0)
#define ONE (1)

/* copied from dynamic_vector.c: 
struct dynamic_vector
{
	void **array; 	  / pointer to the beggining of the dynamic_array   /
	size_t capacity;  / current possible length				 	        /
	size_t size;	  / actual current dynamic_array length 		    /
}; vector_t */

typedef struct heap
{
    int (*cmp_func)(const void *data, const void *param);
    vector_t *vector;
} vector_heap; /* heap_t */

/*************************** Utiliy functions: ********************************/

static size_t GetLeftChildIndex(size_t ParentIndex)
{
    return ((ParentIndex * 2) + 1);
}
/*******/
static size_t GetRightChildIndex(size_t ParentIndex)
{
    return ((ParentIndex * 2) + 2);
}
/*******/
static size_t GetParentIndex(size_t ChildIndex)
{
    return ((ChildIndex - 1) / 2);
}
/*******/
static size_t HasLeftChild(heap_t *heap, size_t index)
{
    return (HeapSize(heap) > GetLeftChildIndex(index) ? 1 : 0);
}
/*******/
static size_t HasRightChild(heap_t *heap, size_t index)
{
    return (HeapSize(heap) > GetRightChildIndex(index) ? 1 : 0);
}
/*******/
/* Get the value inside the node: */
static void *LeftChild(vector_t *vector, size_t index)
{
    return (VectorGetElement(vector, (size_t)GetLeftChildIndex(index)));
}
/*******/
static void *RightChild(vector_t *vector, size_t index)
{
    return (VectorGetElement(vector, GetRightChildIndex(index)));
}

/********************************************************/

static void SwapData(vector_t *vector, size_t index1, size_t index2)
{
    void *index1_data = VectorGetElement(vector, index1);
    void *index2_data = VectorGetElement(vector, index2);

    VectorSetElement(vector, index1, index2_data);
    VectorSetElement(vector, index2, index1_data);
}

/********************************************************/

void PrintHeap(heap_t *heap)
{
    size_t i = 0;
    size_t size = HeapSize(heap);

    for (i = 0; i < size; ++i)
    {
        printf("arr[%ld] = %d\n", i, *(int *)VectorGetElement(heap->vector, i));
    }
}

/********************************************************/

/* compare root node with both children and swap with the smaller one. Keep
   checking and swapping until reaching a node with bigger value. */
static void Heapify(heap_t *heap, size_t index)
{
    size_t root = index;
    size_t bigger_child_index = 0;
    assert(heap);

    /* as link as the node has children - keep going down and check if there
       is need to swap (if parent is smaller than any of his child - swap them).
       I start by checking the left child - because if therre is no left child,
       there is no chance for a right child.
     */
    while (HasLeftChild(heap, root))
    {
        /* smaller-child-index is equal to the smaller of the two children: */
        bigger_child_index = GetLeftChildIndex(root);
        if (HasRightChild(heap, root) &&
            0 < heap->cmp_func(RightChild(heap->vector, root),
                               LeftChild(heap->vector, root)))
        {
            bigger_child_index = GetRightChildIndex(root);
        }

        /* if index is smaller then smaller-child-index - do nothing, else - 
           swap between them: */
        if (0 < (heap->cmp_func(VectorGetElement(heap->vector, root),
                                VectorGetElement(heap->vector, bigger_child_index))))
        {
            break;
        }
        else
        {
            SwapData(heap->vector, root, bigger_child_index);
            root = bigger_child_index;
        }
    }
}

/********************************************************/

void HeapifyUp(heap_t *heap, size_t current)
{
    size_t currents_parent = (current - 1) / 2;
    /* while we haven't reached the root AND the child has greater value than
    parrent - keep swapping: as long as child is smaller than parrent - bubble up */
    while (ZERO < heap->cmp_func(VectorGetElement(heap->vector, current),
                                 VectorGetElement(heap->vector, currents_parent)))
    {
        /* If the child is greater than parent, swap */
        SwapData(heap->vector, current, currents_parent);

        /* if we got to the root - break: */
        if (0 == currents_parent)
        {
            break;
        }

        current = currents_parent;
        currents_parent = GetParentIndex(current);
        if (0 > (int)currents_parent)
        {
            break;
        }
    }
}

/******************************* Prime functions: *****************************/

heap_t *HeapCreate(int (*cmp_func)(const void *data1, const void *data2))
{
    heap_t *new_heap = (heap_t *)malloc(sizeof(heap_t));

    if (!new_heap)
    {
        return (NULL);
    }

    assert(cmp_func);

    new_heap->cmp_func = cmp_func;
    new_heap->vector = VectorCreate(VECTOR_SIZE);

    if (!new_heap->vector)
    {
        free(new_heap);
        new_heap = NULL;

        return (NULL);
    }

    return (new_heap);
}

/******************************************************************************/

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    VectorDestroy(heap->vector);
    free(heap);
    heap = NULL;
}

/******************************************************************************/

int HeapPush(heap_t *heap, const void *data)
{
    size_t current = 0;
    assert(heap);

    current = VectorSize(heap->vector);

    if (0 != VectorPushBack(heap->vector, (void *)data))
    {
        return (1);
    }

    if (0 == current)
    {
        return (0);
    }

    HeapifyUp(heap, current);

    return (0);
}

/******************************************************************************/

void HeapPop(heap_t *heap)
{
    assert(heap);

    if (HeapIsEmpty(heap))
    {
        return;
    }

    SwapData(heap->vector, ZERO, VectorSize(heap->vector) - 1);
    VectorPopBack(heap->vector);

    if (1 < HeapSize(heap))
    {
        Heapify(heap, 0);
    }
}

/******************************************************************************/

void *HeapPeek(const heap_t *heap)
{
    vector_t *vector = NULL;
    assert(heap);

    if (HeapIsEmpty(heap))
    {
        return (NULL);
    }

    vector = heap->vector;

    return (VectorGetElement(vector, ZERO));
}

/******************************************************************************/

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return (VectorSize(heap->vector));
}

/******************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (0 == HeapSize(heap) ? 1 : 0);
}

/******************************************************************************/

void *HeapRemove(heap_t *heap,
                 int (*cond_func)(const void *data, const void *param),
                 const void *param)
{
    size_t i = 0;
    size_t size = 0;
    void *return_data = NULL;
    assert(heap);
    assert(cond_func);

    size = HeapSize(heap);

    for (i = 0; i < size; ++i)
    {
        if (1 == cond_func(VectorGetElement(heap->vector, i), param))
        {
            return_data = VectorGetElement(heap->vector, i);

            /*SwapData(heap->vector, i, (HeapSize(heap) - 1));*/
            VectorSetElement(heap->vector, i,
                             VectorGetElement(heap->vector, size - 1));

            VectorPopBack(heap->vector);

            /* if node is childless and is not the last node in the array: */
            if (i != size - 1)
            {
                if ((2 * i) + 1 >= size && (2 * i) + 2 >= size)
                {
                    HeapifyUp(heap, i);
                }
                else
                {
                    Heapify(heap, i);
                }
            }

            break;
        }
    }

    return (return_data);
}

/******************************************************************************/

static void *RecursiveCheckTree(heap_t *heap, size_t root_index)
{
    size_t left_child_index = 2 * root_index + 1;
    size_t right_child_index = 2 * root_index + 2;
    const size_t heap_size = VectorSize(heap->vector);

    /* check that both childs are smaller than their parent */
    if (left_child_index < heap_size)
    {
        assert(heap->cmp_func(VectorGetElement(heap->vector, root_index),
                              RecursiveCheckTree(heap, left_child_index)) >= 0);
    }

    if (right_child_index < heap_size)
    {
        assert(heap->cmp_func(VectorGetElement(heap->vector, root_index),
                              RecursiveCheckTree(heap, right_child_index)) >= 0);
    }

    return (VectorGetElement(heap->vector, root_index));
}

/******************************************************************************/

void CheckHeap(heap_t *heap)
{
    assert(heap);

    if (HeapIsEmpty(heap))
    {
        return;
    }

    RecursiveCheckTree(heap, 0);
}