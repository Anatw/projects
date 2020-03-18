/*******************************************************************************

Progaram: API to implement a singly linked list
Editor: Lusy Volkov
Date: March 2020
Reviewer: 

*******************************************************************************/
#include <stdio.h>   /* printf() */
#include <stddef.h>  /* size_t */

#include "doubly_linked_list.h"

int Compare(const void *data1, void *data2)
{
	return(*(int *)data1 == *(int *)data2);
}

int AddNumber(void *data, void *param)
{
	*(int *)data = *(int *)data + *(int *)param;
	return (*(int *)data);
}

int main()
{
	dll_t *list1 = NULL;
	dll_t *list2 = NULL;
	
	iter_t iter = NULL;
	iter_t i = NULL;
	
	int var1 = 11;
	int var2 = 22;
	int var3 = 33;
	int var4 = 44;
	int var5 = 55;
	int var6 = 66;
	int var7 = 77;
	int var8 = 88;
	
	list1 = DLLCreate();
	printf("\ncreate the list, the size of it is: %ld\n", DLLSize(list1));
	printf("the list is empty?\n");
	printf("%d\n\n", DLLIsEmpty(list1));
	
	printf("push 6 variables\n");
	DLLPushFront(list1, &var1);
	DLLInsert(DLLBegin(list1), &var2);
	DLLPushBack(list1, &var3);
	DLLInsert(DLLBegin(list1), &var4);
	DLLInsert(DLLBegin(list1), &var5);
	DLLInsert(DLLBegin(list1), &var7);
	printf("size now is: %ld\n\n", DLLSize(list1));
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	printf("\n\npop back and front var\n");
	DLLPopBack(list1);
	DLLPopFront(list1);
	printf("size now is: %ld\n\n", DLLSize(list1));
	
	printf("set and get var6\n");
	iter = DLLBegin(list1); 
	DLLSetData(iter, &var6);
	printf("%d\n\n", *(int *)DLLGetData(iter));
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\n\nis the same iter begin and end?: %d\n", DLLIsSameIter(DLLEnd(list1), DLLBegin(list1)));
	printf("is the same iter end and end?:%d\n", DLLIsSameIter(DLLEnd(list1), DLLEnd(list1)));
	printf("is the list is empty? %d\n", DLLIsEmpty(list1));
	
	printf("remove one element\n");
	DLLRemove(DLLBegin(list1));
	printf("size now is: %ld\n\n", DLLSize(list1));
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\n\nfind var5=55, gets the last elem:\n");
	iter = DLLFind(DLLBegin(list1), DLLEnd(list1), Compare, &var5);
	printf("%d", *(int *)DLLGetData(iter));
	printf("\nfind var2=22\n");
	iter = DLLFind(DLLBegin(list1), DLLEnd(list1), Compare, &var2);
	printf("%d\n", *(int *)DLLGetData(iter));
	
	printf("\nadd var1 = 11 to each element in the list\n");
	DLLForEach(DLLBegin(list1), DLLEnd(list1), AddNumber, &var1);
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	printf("\n");
	
	list2 = DLLCreate();
	printf("insert two elem=55 before splice\n");
	DLLInsert(DLLBegin(list1), &var5);
	DLLInsert(DLLBegin(list1), &var5);
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\n");
	
	printf("\nsplice the list\n");
	DLLSplice(DLLNext(DLLBegin(list1)), DLLPrev(DLLEnd(list1)), DLLBegin(list2));
	
	for (i = DLLBegin(list2); i != DLLNext(DLLEnd(list2)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\n");
	
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\n\ninsert some elements before multifind\n");
	DLLInsert(DLLBegin(list1), &var8);
	DLLInsert(DLLBegin(list1), &var3);
	DLLInsert(DLLBegin(list1), &var7);
	
	printf("\n");
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	printf("\n");
	for (i = DLLBegin(list2); i != DLLNext(DLLEnd(list2)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	
	printf("\nmultifind status: %ld\n", DLLMultiFind(DLLBegin(list2), DLLEnd(list2), &var5, Compare, list1));
	for (i = DLLBegin(list1); i != DLLNext(DLLEnd(list1)); i = DLLNext(i))
	{
		printf(" %d", *(int *)DLLGetData(i));
	}
	printf("\n");
	DLLDestroy(list1);
	DLLDestroy(list2);
	
	return (0);
}	










































