/*******************************************************************************
 * File: binary_search_tree_tests.c - Binary Search Tree test file			   *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Ben David Zikri	                                   			   *
 * Date: 2.4.2020                                                         	   *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

#include "binary_search_tree.h"

int var1 = 10;
int var2 = 7;
int var3 = 1;
int var4 = 12;
int var5 = 14;
int var6 = 13;
int var7 = 5;
int var8 = 8;
int var9 = 9;
int var10 = 15;

/* static void PrintTree(bst_t *tree); */
static int CheckTree(bst_t *tree);

int IntCompare(const void *var1, const void *var2, const void *param);

int IntAdd(void *data, const void *param);

void PrintTree(bst_iter_t t);

/* checking the following functions:
	- BSTCreate
	- BSTDestroy
	- BSTInsert
	- BSTGetData
	- BSTBegin
	- BSTEnd
	- BSTNext
	- BSTPrev
	- BSTIsEqual
	- BSTSize
	- BSTIsEmpty
 */
int BasicTests();

int RemoveTests();

int FindAndForeachTests();

int main()
{
	assert(BasicTests() == 0);
	assert(RemoveTests() == 0);
	assert(FindAndForeachTests() == 0);

	return (0);
}

int BasicTests()
{
	bst_t *new_bst = BSTCreate(IntCompare, NULL);

	assert(BSTSize(new_bst) == 0);
	assert(BSTIsEmpty(new_bst));

	BSTInsert(new_bst, &var1);
	BSTInsert(new_bst, &var2);
	BSTInsert(new_bst, &var3);
	BSTInsert(new_bst, &var4);
	BSTInsert(new_bst, &var5);
	BSTInsert(new_bst, &var6);
	BSTInsert(new_bst, &var7);
	BSTInsert(new_bst, &var8);
	BSTInsert(new_bst, &var9);
	BSTInsert(new_bst, &var10);

	assert(CheckTree(new_bst) == 0);
	assert(BSTGetData(BSTPrev(BSTPrev(BSTEnd(new_bst)))) == (void *)&var5);
	assert(BSTSize(new_bst) == 10);
	assert(!BSTIsEmpty(new_bst));
	
	PrintTree(BSTGetRoot(new_bst));

	/*BSTDestroy(new_bst);*/

	return (0);
}

int RemoveTests()
{
	bst_t *new_bst = BSTCreate(IntCompare, NULL);

	BSTInsert(new_bst, &var1);
	BSTInsert(new_bst, &var2);
	BSTInsert(new_bst, &var3);
	BSTInsert(new_bst, &var4);
	BSTInsert(new_bst, &var5);
	BSTInsert(new_bst, &var6);
	BSTInsert(new_bst, &var7);
	BSTInsert(new_bst, &var8);
	BSTInsert(new_bst, &var9);
	BSTInsert(new_bst, &var10);

	BSTRemove(BSTPrev(BSTPrev(BSTEnd(new_bst))));
	assert(*(int *)BSTGetData(BSTPrev(BSTEnd(new_bst))) == 15);
	
	PrintTree(BSTGetRoot(new_bst));
	
	BSTRemove(BSTBegin(new_bst));
	assert(*(int *)BSTGetData(BSTBegin(new_bst)) == 5);

	PrintTree(BSTGetRoot(new_bst));
	
	BSTRemove(BSTNext(BSTBegin(new_bst)));
	assert(*(int *)BSTGetData(BSTNext(BSTBegin(new_bst))) == 8);

	PrintTree(BSTGetRoot(new_bst));
	
	BSTRemove(BSTPrev(BSTPrev(BSTEnd(new_bst))));
	assert(*(int *)BSTGetData(BSTPrev(BSTPrev(BSTEnd(new_bst)))) == 12);

	PrintTree(BSTGetRoot(new_bst));
	
	BSTRemove(BSTPrev(BSTPrev(BSTPrev(BSTEnd(new_bst)))));
	/*assert(*(int *)BSTGetData(BSTPrev(BSTPrev(BSTPrev(BSTEnd(new_bst))))) == 9);*/

	assert(BSTSize(new_bst) == 6);
	assert(!BSTIsEmpty(new_bst));

	/*BSTDestroy(new_bst);*/

	return (0);
}

int FindAndForeachTests()
{
	bst_t *new_bst = BSTCreate(IntCompare, NULL);
	bst_iter_t iter = NULL;

	BSTInsert(new_bst, &var1);
	BSTInsert(new_bst, &var2);
	BSTInsert(new_bst, &var3);
	BSTInsert(new_bst, &var4);
	BSTInsert(new_bst, &var5);
	BSTInsert(new_bst, &var6);
	BSTInsert(new_bst, &var7);
	BSTInsert(new_bst, &var8);
	BSTInsert(new_bst, &var9);

	/* when element found: */
	assert(BSTIsEqual(BSTFind(new_bst, &var3), BSTBegin(new_bst)));
	/* when element not found: */
	assert(BSTIsEqual(BSTFind(new_bst, &var10), BSTEnd(new_bst)));

	/*BSTForEach(BSTBegin(new_bst), BSTEnd(new_bst), IntAdd, &var10);*/

	for (iter = BSTBegin(new_bst);
		 !BSTIsEqual(iter, BSTPrev(BSTEnd(new_bst)));
		 iter = BSTNext(iter))
	{
		assert(*(int *)BSTGetData(iter) / 10 > 0);
	}

	/*BSTDestroy(new_bst);*/

	return (0);
}

int IntCompare(const void *var1, const void *var2, const void *param)
{
	(void)param;

	return (*(int *)var1 - *(int *)var2);
}

int IntAdd(void *data, const void *param)
{
	*(int *)data = *(int *)data * *(int *)param;

	return (0);
}

static int CheckTree(bst_t *tree)
{
	bst_iter_t iter = NULL;

	for (iter = BSTBegin(tree);
		 !BSTIsEqual(iter, BSTPrev(BSTEnd(tree)));
		 iter = BSTNext(iter))
	{
		assert(*(int *)BSTGetData(iter) < *(int *)BSTGetData(BSTNext(iter)));
	}

	return (0);
}

/*
static void PrintTree(bst_t *tree)
{
	bst_iter_t iter = NULL;

	for (iter = BSTBegin(tree);
		 !BSTIsEqual(iter, BSTEnd(tree));
		 iter = BSTNext(iter))
	{
		printf("data: %d\n", *(int *)BSTGetData(iter));
	}

	printf("\n");
}
*/
