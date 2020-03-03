/*******************************************************************************
 * File: singly_linked_list_tests.c - Singly Linked List DS tests file	       *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Esti Binder				                                       *
 * Date: 2.3.2020	                                                           *
 ******************************************************************************/

#include <stdio.h> /* printf */

#include "singly_linked_list.h"

/* function that compares to ints and return 1 if they equal, 0 if not */
int IntCompare(void *var1, void *var2);

/* function that add 1 to an int */
int IntAdd(void *param, void *data);

int main()
{
	int status = 0;
	SLL_t *my_list = SLLCreate();
	
	iter_t my_iter = 0;
	iter_t i = 0;

	int var1 = 5;
	int var2 = 565;
	int var3 = 13;
	int var4 = 67;
	int var5 = 734;
	int var6 = 345;
	int var7 = 1234;
	
	SLLDestroy(my_list);
	my_list = SLLCreate();
	
	my_iter = SLLBegin(my_list);

	printf("************** Singly Linked List DS Tests: **************\n\n");

	printf("** when the list is empty: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));

	SLLInsert(my_iter, &var1);
	SLLInsert(my_iter, &var2);
	SLLInsert(my_iter, &var3);
	SLLInsert(my_iter, &var4);
	SLLInsert(my_iter, &var5);
	SLLInsert(my_iter, &var6);

	printf("** after inserting 6 elements: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLTail(my_list)); 
		 i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	SLLInsert(SLLTail(my_list), &var7);
	printf("\n** after insert 1 element at end: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLTail(my_list)); 
		 i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	my_iter = SLLRemove(SLLNext(my_iter));

	printf("\n** remove the second element: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLTail(my_list)); 
		 i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	SLLSetData(SLLNext(my_iter), &var5);

	printf("\n** set the 3rd element to 734: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLTail(my_list)); 
		 i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	my_iter = SLLFind(SLLBegin(my_list), SLLTail(my_list), &var4, IntCompare);

	printf("\n** using find function to search 67 **\n");
	printf("The element found! %d\n", *(int *)SLLGetData(my_iter));

	status = SSLForEach(SLLBegin(my_list), SLLTail(my_list), &var1, IntAdd);

	printf("\n** using foreach function to add 5 to each element **\n");
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLTail(my_list)); 
		 i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}


	SLLDestroy(my_list);

	return (0);
}

int IntCompare(void *var1, void *var2)
{
	return (*(int *)var1 == *(int *)var2);
}

int IntAdd(void *param, void *data)
{
	*(int *)data = *(int *)data + *(int *)param;

	return (0); 
}
