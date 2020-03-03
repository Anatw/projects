/*******************************************************************************
					  	 Written by Anat Wax
						  March 3, 2020
						Reviewer: Yoni Naor
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h> /* printf() */

#include "singly_linked_list.h"

int IntCompare(void *x, void *y);
int AddParam( void *param, void *data);

int main()
{
	SLL_t *llist = SLLCreate();
	int data = 4;
	int data2 = 62;
	int data3 = 5;
	int data4 = 6;
	int *p_data = &data;
	int *p_data2 = &data2;
	iter_t node1 = SLLInsert(SLLTail(llist), p_data);
	iter_t node2 = NULL;
	iter_t node3 = NULL;
	iter_t node4 = NULL;
	size_t counter = SLLCount(llist);
	iter_t match = NULL;
	int param = 1;
	iter_t iterator = SLLBegin(llist);
		
	printf("number of members in the list is: %ld\n", counter);
	printf("the data in node1 is: %d\n", *(int *)SLLGetData(node1));	
	SLLSetData(SLLBegin(llist), &data2);
	printf("after set, data in node1: %d\n", *(int *)SLLGetData(node1));
	
	match = SLLFind(SLLBegin(llist), SLLTail(llist), p_data2, IntCompare);
	printf("found a match to %d \n", *(int *)SLLGetData(match));
	
	printf("list is %s\n", (1 == SLLIsEmpty(llist) ? "empty" : "not empty"));
		
	node2 = SLLInsert(SLLTail(llist), p_data);
	printf("the data in node2 is: %d\n", *(int *)SLLGetData(node2));
	
	node3 = SLLInsert(SLLTail(llist), &data3);
	printf("the data in node3 is: %d\n", *(int *)SLLGetData(node3));
	
	node4 = SLLInsert(SLLTail(llist), &data4);
	printf("the data in node4 is: %d\n", *(int *)SLLGetData(node4));
	
	printf("\nnumber of members in the list is: %ld\n\n", SLLCount(llist));
	
		for(iterator = SLLBegin(llist); !SLLIsSameIter(iterator,
				SLLTail(llist)); iterator = SLLNext(iterator))
	{
		printf("the next node data is: %d\n", *(int *)SLLGetData(iterator));
	}
	
	SLLForEach(SLLBegin(llist), SLLTail(llist), &param, AddParam);
	printf("\nafter 'ForEach': add 1:\n");
	
	for(iterator = SLLBegin(llist); !SLLIsSameIter(iterator,
			SLLTail(llist)); iterator = SLLNext(iterator))
	{
		printf("the next node data is: %d\n", *(int *)SLLGetData(iterator));
	}
	
	SLLDestroy(llist);

	return (0);
}

int IntCompare(void *x, void *y)
{
	return ((*(int *)x == *(int *)y) ? 1 : 0);
}

int AddParam(void *param, void *data)
{
	*(int *)data = *(int *)param + *(int *)data;
	
	return (0);
}
