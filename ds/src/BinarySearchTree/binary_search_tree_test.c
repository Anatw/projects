/*******************************************************************************
					  		 Written by Anat Wax
						  March 31 - April 3rd, 2020
							 Reviewer: Amir Paz
*******************************************************************************/
#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /*assert() */

#include "binary_search_tree.h"

int cmp_func(const void *data1, const void *data2, const void *param);
void PrintTree(bst_iter_t t);
int BSTDuplicat(const void *data, const void *param);

int main()
{
	int data = 5;
	int data2 = 1;
	int data3 = 20;
	int data4 = 5;
	int data5 = 9;
	int data6 = 30;
	int data7 = 100;
	int data8 = 95;
	int data9 = 93;
	int data10 = 2;
	int data11 = 6;
	int data12 = 8;
	int data13 = 7;
	
	int param = 2;
	
	        
	bst_iter_t begin_node = NULL;
	bst_iter_t begin_node2 = NULL;
	bst_iter_t iterator = NULL;
	bst_t *tree = BSTCreate(cmp_func, NULL);
		
	BSTInsert(tree, &data);
	begin_node = BSTInsert(tree, &data2);
	begin_node2 = BSTInsert(tree, &data3);
	BSTInsert(tree, &data5);
	BSTInsert(tree, &data6);
	BSTInsert(tree, &data7);
	BSTInsert(tree, &data8);
	BSTInsert(tree, &data9);
	BSTInsert(tree, &data10);
	BSTInsert(tree, &data11);
	BSTInsert(tree, &data12);
	BSTInsert(tree, &data13);
	
	/*printf("the data in begin_node2 is: %d\n", *(int *)BSTGetData(begin_node2));*/
	printf("are first and third iterators equal? %s\n", (1 == BSTIsEqual(begin_node, begin_node2) ? "yes": "no"));
	
	/*printf("BSTBegin: %d\n", *(int *)BSTGetData(BSTBegin(tree)));*/
	
	assert(NULL != BSTEnd(tree));
	
	/*printf("BSTFind: found 5? %d\n", *(int *) BSTGetData(BSTFind(tree, &data4)));*/
	
	PrintTree(BSTGetRoot(tree));
	
	BSTRemove(begin_node2);
	
	
	/*printf("BSTPrev: entered - 20: %d\n", *(int *)BSTGetData(BSTPrev(begin_node2)));*/
	printf("The size of the tree is %ld nodes\n", BSTSize(tree));
	
	printf("is tree empty? %s\n",(1 == BSTIsEmpty(tree) ? "yes" : "no"));
	
	
	
	/*printf("BSTNext: of - 5: %d\n", *(int *)BSTGetData(BSTNext(begin_node2)));*/
	
	PrintTree(BSTGetRoot(tree));
	
	printf("running ForEach - multiplying by 2:\n");
	BSTForEach (BSTBegin(tree), BSTEnd(tree), BSTDuplicat, &param);
	PrintTree(BSTGetRoot(tree));
	
	/*for (iterator = BSTBegin(tree); !BSTIsEqual(iterator, BSTPrev(BSTEnd(tree)));
		 iterator = BSTEnd(tree))
	{
		assert(*(int *)BSTGetData(iterator) / 10 > 0);
		printf("%d\n", *(int *)BSTGetData(iterator));
	}*/
	printf("The size of the tree is %ld nodes\n", BSTSize(tree));
	BSTDestroy(tree);
	
	
		return (0);
}

/* returns 1 if should go right and -1 if should go right, 0 if equal */
int cmp_func(const void *data1, const void *data2, const void *param)
{
	if (*(int *)data1 > *(int *)data2)
	{
		return (1);
	}
	else if (*(int *)data1 < *(int *)data2)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

int BSTDuplicat(const void *data, const void *param)
{
	assert(data);
	assert(param);
	
	*(int *)data *= *(int *)param;
	
	return (0);
}
