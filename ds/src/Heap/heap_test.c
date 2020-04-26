#include <stdio.h> /* printf(), size_t */

#include "utility.h"
#include "heap.h"


int heap_cmp_func(const void *data1, const void *data2);

int main ()
{
    int data1 = 6;
    int data2 = 90;
    int data3 = 5;
    int data4 = 34;
    int data5 = 12;
    int data6 = 9;
    int data7 = 2;
    int data8 = 100;
    int data9 = 10;
    int data10 = 7;
    heap_t *heap = HeapCreate(CmpFunc);
    
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

    printf("peek: %d\n", *(int *)HeapPeek(heap));
    printf("popping data1    \n");
    HeapPop(heap);
     printf("peek: %d\n", *(int *)HeapPeek(heap));
    printf("popping data2    \n");
    HeapPop(heap);
    HeapDestroy(heap);
    printf("ehcck\n");
    return (0);
}

/* this cmp_func create a min heap (smallest value is the root): */
