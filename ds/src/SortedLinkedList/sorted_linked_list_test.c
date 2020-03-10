#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */

#include "sorted_linked_list.h"

int IsBefore(void *data1, void *data2);
int DLLIntCompare(const void *x, const void *y);
int DLLAddParam(void *param, void *data);
void SDLLPrint(dsll_t *list);

int main()
{
	int data1 = 2;
	int data2 = 8;
	
	dsll_t *slist = DSLLCreate(IsBefore);
	DSLLInsert(slist, &data1);
	printf("size is (1): %ld\n", DSLLSize(slist));
	DSLLInsert(slist, &data2);
	printf("data is: %d\n", *(int *)DSLLGetData(DSLLBegin(slist)));
	printf("size is (2): %ld\n", DSLLSize(slist));
	DSLLInsert(slist, &data2);
	DSLLInsert(slist, &data1);
	printf("Printing the list: \n");
	SDLLPrint(slist);
	DSLLRemove(DSLLPrev(DSLLEnd(slist)));
	printf("DSLLRemove: Printing the list: \n");
	SDLLPrint(slist);
	DSLLPopFront(slist);
	
	
	printf("DSLLPopFront: Printing the list: \n");
	SDLLPrint(slist);
	
	DSLLPopBack(slist);
	printf("DSLLPopBack: Printing the list: \n");
	SDLLPrint(slist);
	
	
	DSLLDsetroy(slist);

	return (0);
}

/* return 1 if data1 is bedore data2 (data1 is smaller than data2).
 * 0 if data2 if not (= / >) */
int IsBefore(void *data1, void *data2)
{
	if (data1 < data2)
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

int DLLAddParam(void *param, void *data)
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
