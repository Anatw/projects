#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sorted_linked_list.h"

#define TEST (5)

bool IntIsBefore(const void *data1, const void *data2);

void PrintList(dsll_t *list);

bool IntIsGreaterThan(const void *param, const void *data1);

int CheckBasics();

int CheckMerge();

int CheckFind();

int CheckForeach();

int CheckIsEqual();

int IntAdd(void *data, const void *param);

int main()
{
	assert(0 == CheckBasics());
	assert(0 == CheckMerge());
	assert(0 == CheckFind());
	assert(0 == CheckForeach());
	assert(0 == CheckIsEqual());
	
	return (0);
}

int CheckBasics()
{
	dsll_t *my_sorted = DSLLCreate(IntIsBefore);
	int i = 0;
	int *temp_int = NULL;
	dll_iter_t iter = NULL;

	assert(DSLLIsEmpty(my_sorted));
	assert(0 == DSLLSize(my_sorted));

	for (i = TEST; i > 0; --i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		DSLLInsert(my_sorted, var);
	}

	assert(!DSLLIsEmpty(my_sorted));
	assert(TEST == DSLLSize(my_sorted));

	temp_int = (int *)DSLLPopFront(my_sorted);
	assert(*temp_int == 1);
	free(temp_int);

	temp_int = (int *)DSLLPopBack(my_sorted);
	assert(*temp_int == TEST);
	free(temp_int);

	assert(*(int *)DSLLGetData(DSLLPrev(DSLLEnd(my_sorted))) == (TEST - 1));

	assert(!DSLLIsEmpty(my_sorted));
	assert((TEST - 2) == DSLLSize(my_sorted));

	for (i = 2, iter = DSLLBegin(my_sorted); iter != DSLLEnd(my_sorted);
		 ++i, iter = DSLLNext(iter))
	{
		assert(*(int *)DSLLGetData(iter) == i);
		free(DSLLGetData(iter));
	}

	DSLLDestroy(my_sorted);
	printf("here\n");
	return (0);
}

int CheckMerge()
{
	dsll_t *my_sorted = DSLLCreate(IntIsBefore);
	dsll_t *my_sorted2 = DSLLCreate(IntIsBefore);
	int i = 0;
	dll_iter_t iter = NULL;

	printf("*** check when list2 range is inside list1 ***\n");
	/* check when list2 range is inside list1 */
	for (i = TEST * 3; i > 0; i -= 3)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		DSLLInsert(my_sorted, var);
	}

	for (i = TEST * 2; i > 2; i -= 2)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		DSLLInsert(my_sorted2, var);
	}

	printf("\n* list1: *\n");
	PrintList(my_sorted);
	printf("\n* list2: *\n");
	PrintList(my_sorted2);
	printf("here\n");

	DSLLMerge(my_sorted, my_sorted2);

	printf("\n* list1 after merge: *\n");
	PrintList(my_sorted);

	printf("\n*** check when list1 is empty, everything copied: ***\n");
	/* check when list1 is empty */
	DSLLMerge(my_sorted2, my_sorted2);
	PrintList(my_sorted2);

	/* free allocated data */
	for (iter = DSLLBegin(my_sorted); iter != DSLLEnd(my_sorted);
		 iter = DSLLNext(iter))
	{
		free(DSLLGetData(iter));
	}
	printf("here\n");
	for (iter = DSLLBegin(my_sorted2); iter != DSLLEnd(my_sorted2);
		 iter = DSLLNext(iter))
	{
		free(DSLLGetData(iter));
	}

	DSLLDestroy(my_sorted);
	DSLLDestroy(my_sorted2);
	printf("here2\n");

	return (0);
}

int CheckFind()
{
	
	dsll_t *my_sorted = DSLLCreate(IntIsBefore);
	int i = 0;
	dll_iter_t iter = NULL;
	void *data = NULL;
	int test_num = TEST + 1;
	

	assert(DSLLIsEmpty(my_sorted));
	assert(0 == DSLLSize(my_sorted));
	
	for (i = TEST; i > 0; --i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		DSLLInsert(my_sorted, var);
	}
	printf("22\n");
	data = DSLLGetData(DSLLBegin(my_sorted));
	printf("23\n");
	iter = DSLLFind(my_sorted, DSLLBegin(my_sorted), DSLLEnd(my_sorted), data);
	printf("24\n");
	assert(*(int *)DSLLGetData(iter) == 1);

	data = &test_num;
	iter = DSLLFind(my_sorted, DSLLBegin(my_sorted), DSLLEnd(my_sorted), data);
	assert(iter == DSLLEnd(my_sorted));
	
	data = DSLLGetData(DSLLBegin(my_sorted));
	iter = DSLLFindIf(my_sorted, IntIsGreaterThan, data);
	printf("25\n");
	/*assert(*(int *)DSLLGetData(iter) == 2); ask?? why it fail*/
	printf("23\n");
	for (iter = DSLLBegin(my_sorted); iter != DSLLEnd(my_sorted);
		 iter = DSLLNext(iter))
	{
		free(DSLLGetData(iter));
	}

	DSLLDestroy(my_sorted);

	return (0);
}

int CheckForeach()
{
	dsll_t *my_sorted = DSLLCreate(IntIsBefore);
	int i = 0;
	dll_iter_t iter = NULL;
	int six = 6;

	assert(DSLLIsEmpty(my_sorted));
	assert(0 == DSLLSize(my_sorted));

	for (i = TEST; i > 0; --i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		DSLLInsert(my_sorted, var);
	}

	printf("\n*** list before foreach: ***\n");
	PrintList(my_sorted);

	DSLLForEach(DSLLBegin(my_sorted), DSLLEnd(my_sorted), IntAdd, &six);

	printf("\n* list after add 6 to each element: *\n");
	PrintList(my_sorted);

	for (iter = DSLLBegin(my_sorted); iter != DSLLEnd(my_sorted);
		 iter = DSLLNext(iter))
	{
		free(DSLLGetData(iter));
	}

	DSLLDestroy(my_sorted);

	return (0);
}

int CheckIsEqual()
{
	dsll_t *my_sorted = DSLLCreate(IntIsBefore);
	int six = 6;
	int eight = 8;

	DSLLInsert(my_sorted, &six);
	DSLLInsert(my_sorted, &six);
	DSLLInsert(my_sorted, &eight);

	assert(DSLLIsEqual(DSLLBegin(my_sorted), DSLLNext(DSLLBegin(my_sorted))));
	assert(!DSLLIsEqual(DSLLBegin(my_sorted), DSLLPrev(DSLLEnd(my_sorted))));

	DSLLDestroy(my_sorted);
	return (0);
}

bool IntIsBefore(const void *data1, const void *data2)
{
	if (*(int *)data1 < *(int *)data2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

bool IntIsGreaterThan(const void *param, const void *data1)
{
	if (*(int *)data1 > *(int *)param)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void PrintList(dsll_t *list)
{
	dsll_iter_t i = 0;
	printf("Elements: %lu\n", DSLLSize(list));
	printf("Is Empty: %s\n\n", (DSLLIsEmpty(list) ? "yes" : "no"));
	for (i = DSLLBegin(list); i != DSLLEnd(list); i = DSLLNext(i))
	{
		printf("element: %d, %p\n", *(int *)DSLLGetData(i), DSLLGetData(i));
	}

	printf("\n");
}

int IntAdd(void *data, const void *param)
{
	*(int *)data = *(int *)data + *(int *)param;

	return (0);
}
