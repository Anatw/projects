#include <stdlib.h>
#include <stdio.h> /* printf() */

#include "singly_linked_list.h"

int IntCompare(void *x, void *y);

int main()
{
	SLL_t *llist = SLLCreate();
	int data = 4;
	int data2 = 62;
	int *p_data = &data;
	int *p_data2 = &data2;
	iter_t head = SLLBegin(llist);
	iter_t tail = SLLTail(llist);
	iter_t node1 = SLLInsert(tail, p_data);
	size_t counter = SLLCount(llist);
	iter_t match = NULL;
		
	printf("number of members in the list is: %ld\n", counter);
	printf("the data in head is: %d\n", *(int *)SLLGetData(head));	
	SLLSetData(head, &data2);
	printf("after set, data in head: %d\n", *(int *)SLLGetData(head));
	
	match = SLLFind(head, tail, p_data2, IntCompare);
	printf("found a match to %d \n", *(int *)SLLGetData(match));
	
	printf("list is %s\n", (1 == SLLIsEmpty(llist) ? "empty" : "not empty"));
		
	return (0);
}

int IntCompare(void *x, void *y)
{
	return ((*(int *)x == *(int *)y) ? 0 : 1);
}
