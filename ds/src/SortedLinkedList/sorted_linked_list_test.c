/*******************************************************************************
					  	 Written by Anat Wax
						    March 9-11, 2020
						Reviewer: Lior Cohen
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#include "sorted_linked_list.h"

int IsBefore(void *data1, void *data2);
int DSLLIntCompare(const void *x, const void *y);
int DSLLAddParam(void *param, void *data);
void SDLLPrint(dsll_t *list);
int DSLLIntCompare(const void *x, const void *y);

int main()
{
	int data1 = 2;
	int data2 = 8;
	int data3 = 5;
	int data4 = 2;
	int data5 = 8;
	int data6 = 1;
	int data7 = 3;
	int data8 = 10;
	int data9 = 5;
	int add2 = 2;
	iter_t match = NULL;
		
	dsll_t *slist = DSLLCreate(IsBefore);
	dsll_t *slist2 = DSLLCreate(IsBefore);
	printf("creating list 'slist':\n");
	
	printf("inserting 2:\n");
	DSLLInsert(slist, &data1);
	printf("size is (1): %ld\n", DSLLSize(slist));
	
	printf("inserting 8:\n");
	DSLLInsert(slist, &data2);

	printf("inserting 8:\n");
	DSLLInsert(slist, &data5);
	
	printf("inserting 5:\n");
	DSLLInsert(slist, &data3);
	
	printf("inserting 2:\n");
	DSLLInsert(slist, &data4);
	
	printf("\nPrinting list 'slist': \n");
	SDLLPrint(slist);
	
	DSLLInsert(slist2, &data6);
	DSLLInsert(slist2, &data7);
	DSLLInsert(slist2, &data8);
	DSLLInsert(slist2, &data9);
	
	printf("\nPrinting list 'slist2': \n");
	SDLLPrint(slist2);
	
	DSLLMerge(slist, slist2);
	printf("\nPrinting list 'slist': \n");
	SDLLPrint(slist);
	/*
	DSLLForEach(DSLLBegin(slist), DSLLEnd(slist), DSLLAddParam, &add2);

	printf("is data in begin (%d) equal to the data in the tail (%d) ? %s\n",
		   *(int *)(DSLLGetData(DSLLBegin(slist))),
		   *(int *)(DSLLGetData(DSLLPrev(DSLLEnd(slist)))),
		   (DSLLIsEqual(DSLLBegin(slist), DSLLPrev(DSLLEnd(slist))) ? "yes" : "no"));
	printf("is data in begin (%d) equal to the data in the next data (%d)? %s\n",
		   *(int *)(DSLLGetData(DSLLBegin(slist))),
		   *(int *)(DSLLGetData(DSLLNext(DSLLBegin(slist)))),
		   (DSLLIsEqual(DSLLBegin(slist), DSLLNext(DSLLBegin(slist))) ? "yes" : "no"));
	printf("\nAdding 2 to each member, printing the list: \n");
	SDLLPrint(slist);*/
	/* checking DSLLFindIf:
	match = DSLLFindIf(DSLLBegin(slist), DSLLEnd(slist), DSLLIntCompare, &data2);
	printf("DSLLFind (8): %d\n", *(int *)DLLGetData(match));
	*/
	
	/* checking DSLLFind: - without list
	match = DSLLFind(DSLLBegin(slist), DSLLEnd(slist), &data2);
	printf("DSLLFind (8): %d\n", *(int *)DLLGetData(match));
	*/
	/* checking DSLLFind: - with list: */
	match = DSLLFind(slist, DSLLBegin(slist), DSLLEnd(slist), &data2);
	printf("DSLLFind (8): %d\n", *(int *)DLLGetData(match));
	
	/* checking for the first member:
	printf("data of first member is (2): %d\n", *(int *)DSLLGetData(DSLLBegin(slist)));
	printf("size is (2): %ld\n", DSLLSize(slist));
	*/
	
	/* check removing funcs:
	printf("\nDSLLRemove: Printing the list: \n");
	DSLLRemove(DSLLPrev(DSLLEnd(slist)));
	SDLLPrint(slist);LAddPar
		
	printf("\nDSLLPopFront: Printing the list: \n");
	DSLLPopFront(slist);
	SDLLPrint(slist);
	
	printf("\nDSLLPopBack: Printing the list: \n");
	DSLLPopBack(slist);
	SDLLPrint(slist);
	*/
	
	DSLLDsetroy(slist);
	DSLLDsetroy(slist2);

	return (0);
}

/* return 1 if data1 is bedore data2 (data1 is smaller than data2).
 * 0 if data2 if not (= / >) */
int IsBefore(void *data1, void *data2)
{
	if (*(int *)data1 < *(int *)data2)
	{
		return (1);
	}
	
	return (0);
}

/* IntCompare: 1 = members are identical, 0 = members are different */
int DLLIntCompare(const void *x, const void *y)
{
	return ((*(int *)x == *(int *)y) ? 1 : 0);
}

int DSLLAddParam(void *param, void *data)
{
	*(int *)data = *(int *)param + *(int *)data;
	
	return (0);
}

void SDLLPrint(dsll_t *list)
{
	dsll_iter_t i = 0;
	printf("Elements: %lu\n", DSLLSize(list));
	printf("Is Empty: %s\n\n", (DSLLIsEmpty(list) ? "yes" : "no"));
	for (i = DSLLBegin(list); i != DSLLEnd(list); i = DSLLNext(i))
	{
		printf("element: %d\n", *(int *)DSLLGetData(i));
	}

	printf("\n");
}


int DSLLIntCompare(const void *x, const void *y)
{
	return ((*(int *)x == *(int *)y) ? 1 : 0);
}


