#include <stdio.h> /* printf() */

#include "doubly_linked_list.h"

int DLLIntCompare(const void *x, const void *y);
int DLLAddParam(void *param, void *data);


int main()
{
	dll_t *new_list = DLLCreate();
	int data1 = 3;
	int data2 = 4;
	int data3 = 8;
	int data4 = 20;
	iter_t new_node = NULL;
	iter_t new_node2 = NULL;
	iter_t match = NULL;
	int param = 2;
		
	
	new_node = DLLPushFront((new_list), &data1); /* 3 */
	printf("the content of the newly entered node is (3): %d\n",
		   *(int *)DLLGetData(new_node));
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	printf("is the list empty? %s\n", (1 == DLLIsEmpty(new_list)) ? "yes" : "no");
	
	DLLInsert(DLLBegin(new_list), &data2); /* 4 3 */
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	
	new_node2 = DLLInsert(DLLBegin(new_list), &data3); /* 8 4 3 */
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	
	DLLInsert(DLLEnd(new_list), &data4); /* 8 4 3 20 */
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	
	printf("DLLPushBack:\n");
	DLLPushBack((new_list), &data2);	/* 8 4 3 20 4 */
	printf("the value of the lase node is %d\n", *(int *)DLLGetData(DLLPrev(DLLEnd(new_list))));
	
	match = DLLFind(DLLBegin(new_list), DLLEnd(new_list), &data2,
			DLLIntCompare);
	printf("looking for '4': %d\n", *(int *)DLLGetData(match));
	
	printf("\ncurrent SIZE is: %ld\n", DLLSize(new_list));
	printf("Printing the list: \n");
	DLLPrint(new_list);
	
	printf("DLLPopBack:\n");
	printf("before: current SIZE is: %ld\n", DLLSize(new_list));
	DLLPopBack(new_list);
	printf("after: current SIZE is: %ld\n", DLLSize(new_list));
	
	printf("DLLPopFront:\n");
	printf("before: current SIZE is: %ld\n", DLLSize(new_list));
	DLLPopFront(new_list);
	printf("after DLLPopFront: current SIZE is: %ld\n\n", DLLSize(new_list));
	
	/* problem start here: */
	
	printf("Printing the list: \n");
	DLLPrint(new_list);
	
	DLLRemove(new_node2);
	printf("one node removed\n");
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	
	
	DLLInsert(DLLBegin(new_list), &data3); /* 4 3 */
	printf("current SIZE is: %ld\n", DLLSize(new_list));
	
	DLLInsert(DLLEnd(new_list), &data4); /* 8 4 3 20 */
	printf("current SIZE is: %ld\n\n", DLLSize(new_list));
	
	DLLPrint(new_list);
	
	DLLForEach(DLLBegin(new_list), DLLEnd(new_list), DLLAddParam, &param);
	DLLPrint(new_list);
	
	DLLDestroy(new_list);
	
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
