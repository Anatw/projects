/*******************************************************************************
 * File: avl_tree_tests.c - AVL Tree tests file				 		           *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Amir Paz	                                   			   	   *
 * Date: 11.4.2020                                                         	   *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <stdio.h>	/* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, rand, srand, free */
#include <time.h>	/* time */

#include "avl_tree.h"

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
int var11 = 4;
int var12 = 3;

int IntCompare(const void *var1, const void *var2);

int IntAdd(void *data, void *param);

/*
testing:
create
destroy
insert
count
is empty
*/
int BasicTests();

int RemoveTests();

int FindAndForeachTests();

int LoadTests();

int main()
{
	assert(BasicTests() == 0);
	assert(RemoveTests() == 0);
	assert(FindAndForeachTests() == 0);
	/*assert(LoadTests() == 0);*/
	return (0);
}

int BasicTests()
{
	avl_t *new_avl = AVLCreate(IntCompare);

	assert(AVLCount(new_avl) == 0);
	assert(AVLIsEmpty(new_avl));

	AVLInsert(new_avl, &var1);
	AVLInsert(new_avl, &var2);
	AVLInsert(new_avl, &var3);
	AVLInsert(new_avl, &var4);
	AVLInsert(new_avl, &var5);
	AVLInsert(new_avl, &var6);
	AVLInsert(new_avl, &var7);
	AVLInsert(new_avl, &var8);
	AVLInsert(new_avl, &var9);
	AVLInsert(new_avl, &var10);
	AVLInsert(new_avl, &var11);
	AVLInsert(new_avl, &var12);

	printf("Tree: \n");
	InOrderTraversalPrint(new_avl);

	assert(AVLCount(new_avl) == 12);
	assert(AVLHeight(new_avl) == 3);
	assert(!AVLIsEmpty(new_avl));

	AVLDestroy(new_avl);

	return (0);
}

int RemoveTests()
{
	avl_t *new_avl = AVLCreate(IntCompare);

	assert(AVLCount(new_avl) == 0);
	assert(AVLIsEmpty(new_avl));

	AVLInsert(new_avl, &var1);
	AVLInsert(new_avl, &var2);
	AVLInsert(new_avl, &var3);
	AVLInsert(new_avl, &var4);
	AVLInsert(new_avl, &var5);
	AVLInsert(new_avl, &var6);
	AVLInsert(new_avl, &var7);
	AVLInsert(new_avl, &var8);
	AVLInsert(new_avl, &var9);
	AVLInsert(new_avl, &var10);
	AVLInsert(new_avl, &var11);
	AVLInsert(new_avl, &var12);

	assert(AVLCount(new_avl) == 12);
	assert(AVLHeight(new_avl) == 3);
	assert(!AVLIsEmpty(new_avl));

	AVLRemove(new_avl, &var2);
	printf("\nTree after removing 7: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 3);
	assert(AVLCount(new_avl) == 11);

	AVLRemove(new_avl, &var12);
	printf("\nTree after removing 3: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 3);
	assert(AVLCount(new_avl) == 10);

	AVLRemove(new_avl, &var10);
	printf("\nTree after removing 15: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 3);
	assert(AVLCount(new_avl) == 9);

	AVLRemove(new_avl, &var5);
	printf("\nTree after removing 14: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 3);
	assert(AVLCount(new_avl) == 8);

	AVLRemove(new_avl, &var3);
	printf("\nTree after removing 1: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 3);
	assert(AVLCount(new_avl) == 7);

	AVLRemove(new_avl, &var4);
	printf("\nTree after removing 12: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 2);
	assert(AVLCount(new_avl) == 6);

	AVLRemove(new_avl, &var7);
	AVLRemove(new_avl, &var11);
	printf("\nTree after removing 4 and 5: \n");
	InOrderTraversalPrint(new_avl);
	assert(AVLHeight(new_avl) == 2);
	assert(AVLCount(new_avl) == 4);

	AVLDestroy(new_avl);

	return (0);
}

int FindAndForeachTests()
{
	avl_t *new_avl = AVLCreate(IntCompare);

	assert(AVLCount(new_avl) == 0);
	assert(AVLIsEmpty(new_avl));

	AVLInsert(new_avl, &var1);
	AVLInsert(new_avl, &var2);
	AVLInsert(new_avl, &var4);
	AVLInsert(new_avl, &var5);
	AVLInsert(new_avl, &var6);
	AVLInsert(new_avl, &var7);
	AVLInsert(new_avl, &var8);
	AVLInsert(new_avl, &var9);
	AVLInsert(new_avl, &var10);
	AVLInsert(new_avl, &var11);

	printf("\nBefore foreach:\n");
	InOrderTraversalPrint(new_avl);

	AVLForEach(new_avl, IntAdd, &var12);
	printf("\nAfter foreach, multiplied by 3:\n");
	InOrderTraversalPrint(new_avl);

	assert(*(int *)AVLFind(new_avl, &var4) == var4);
	assert(AVLFind(new_avl, &var3) == NULL);

	AVLDestroy(new_avl);

	return (0);
}

int LoadTests()
{
	avl_t *new_avl = AVLCreate(IntCompare);
	size_t i = 0;
	int *int_p = NULL;

	srand(time(NULL));

	for (i = 0; i < 50000; ++i)
	{
		int_p = (int *)malloc(sizeof(int));
		*int_p = rand();

		AVLInsert(new_avl, int_p);
	}

	printf("\n50,000 items:\n");
	InOrderTraversalPrint(new_avl);
	printf("\n50,000 items tree height: %ld\n", AVLHeight(new_avl));
	printf("\n50,000 items tree count: %ld\n", AVLCount(new_avl));

	AVLDestroy(new_avl);

	return (0);
}

int IntAdd(void *data, void *param)
{
	*(int *)data = *(int *)data * *(int *)param;

	return (0);
}

int IntCompare(const void *var1, const void *var2)
{
	return (*(int *)var1 - *(int *)var2);
}
