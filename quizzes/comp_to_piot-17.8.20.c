/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20

compile: gd comp_to_piot-17.8.20.c doubly_linked_list.c -o
comp_to_piot-17.8.20.out
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

#include "../ds/include/doubly_linked_list.h"

void Swap(iter_t first, iter_t second)
{
    iter_t sec_next = DLLNext(second);
    iter_t sec_temp = DLLNext(second);
    iter_t first_temp_prev = DLLNext(DLLPrev(first));
    iter_t first_temp = DLLNext(first);
    sec_temp = first;
    first_temp_prev = second;
    first_temp = sec_next;
}

void CompToPivot(dll_t* list, int pivot)
{
    iter_t end = DLLEnd(list);
    iter_t node = DLLBegin(list);

    while (!DLLIsSameIter(end, node))
    {
        if (*(int*)DLLGetData(node) < pivot)
        {
            node = DLLNext(node);
        }
        else
        {
            if (*(int*)DLLGetData(DLLNext(node)) <= pivot)
            {
                node = DLLNext(node);
                while ((*(int*)DLLGetData(node) > pivot) &&
                       (DLLIsSameIter(DLLBegin(list), node)))
                {
                    Swap(node, DLLNext(node));
                }
            }

            node = DLLNext(node);
        }
    }
}

int main()
{
    dll_t* list = DLLCreate();
    int data1 = 1;
    int data2 = 9;
    int data3 = 5;
    int data4 = 9;
    int data5 = 9;
    int data6 = 4;
    int data7 = 6;

    DLLInsert(DLLBegin(list), &data1);
    DLLInsert(DLLBegin(list), &data2);
    DLLInsert(DLLBegin(list), &data3);
    DLLInsert(DLLBegin(list), &data4);
    DLLInsert(DLLBegin(list), &data5);
    DLLInsert(DLLBegin(list), &data6);
    DLLInsert(DLLBegin(list), &data7);

    printf("before:\n");
    DLLPrint(list);

    CompToPivot(list, 7);

    printf("after:\n");
    DLLPrint(list);

    return (0);
}
