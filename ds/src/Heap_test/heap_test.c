/*******************************************************************************
					  	   Written by Anat Wax
						  23-27 of April, 2020
						Reviewer: Yonathan Berdugo
*******************************************************************************/
/*#include <stdio.h> 

#include "utility.h"
#include "heap.h"

int IsDevidable(const void *data, const void *param);

int IsDevidableSeven(const void *data, const void *param);
int IsDevidableFive(const void *data, const void *param);*/

int main()
{
   /* int data1 = 6;
    int data2 = 93;
    int data3 = 5;
    int data4 = 34;
    int data5 = 12;
    int data6 = 9;
    int data7 = 2;
    int data8 = 101;
    int data9 = 11;
    int data10 = 7;
    int param = 6;
    heap_t *heap = HeapCreate(IntCmpFunc);
    printf("The heap is%s empty\n", (!HeapIsEmpty(heap) ? " not" : ""));

    printf("inserting data1\n");
    HeapPush(heap, &data1);
    printf("inserting data2\n");
    HeapPush(heap, &data2);
    printf("inserting data3\n");
    HeapPush(heap, &data3);
    printf("inserting data4\n");
    HeapPush(heap, &data4);
    printf("inserting data5\n");
    HeapPush(heap, &data5);
    printf("inserting data6\n");
    HeapPush(heap, &data6);
    HeapPush(heap, &data7);
    HeapPush(heap, &data8);
    HeapPush(heap, &data9);
    printf("inserting data10\n");
    HeapPush(heap, &data10);

    PrintHeap(heap);
    printf("The current size of the heap is %ld members\n", HeapSize(heap));
    printf("The heap is%s empty\n\n", (!HeapIsEmpty(heap) ? " not" : ""));

    printf("IsDevidableSeven:\n");
    printf("\nHeapRemove:\n");
    printf("element removed: %d\n", *(int *)HeapRemove(heap, IsDevidableSeven, &param));

    printf("IsDevidableFive:\n");
    printf("element removed: %d\n", *(int *)HeapRemove(heap, IsDevidableFive, &param));

    printf("\npopping data1    \n");
    HeapPop(heap);
    PrintHeap(heap);
    CheckHeap(heap);
    printf("peek: %d\n", *(int *)HeapPeek(heap));
    printf("popping data2    \n\n");
    HeapPop(heap);

    printf("\nThe current size of the heap is %ld members\n", HeapSize(heap));
    PrintHeap(heap);
    CheckHeap(heap);
    printf("\nHeapRemove (element removed (param = %d)):\n", param);
    printf("element removed (param = %d): %d\n", param, *(int *)HeapRemove(heap, IsDevidable, &param));
    PrintHeap(heap);
    CheckHeap(heap);
    printf("\nThe current size of the heap is %ld members\n\n", HeapSize(heap));

    printf("\n\npeek: %d\n", *(int *)HeapPeek(heap));

    HeapDestroy(heap);
    printf("ehcck\n");*/
    return (0);
}

/* returns 0 if succedded, 1 if failed. */
/*int IsDevidable(const void *data, const void *param)
{
    if (0 == (*(int *)data % *(int *)param))
    {
        return (1);
    }

    return (0);
}

int IsDevidableSeven(const void *data, const void *param)
{
    int new_param = 7;
    UNUSED(param);
    if (0 == (*(int *)data % new_param))
    {
        return (1);
    }

    return (0);
}
int IsDevidableFive(const void *data, const void *param)
{
    int new_param = 5;
    UNUSED(param);
    if (0 == (*(int *)data % new_param))
    {
        return (1);
    }

    return (0);
}*/