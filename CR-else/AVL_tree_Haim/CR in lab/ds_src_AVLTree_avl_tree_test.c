/*******************************************************************************

File: avltree_test.c
Purpose: test the functions to implement AVL Tree
Date: April 2020
Author: Haim Saadia
Reviewer: Anat Wax

*******************************************************************************/

#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

#include "avl_tree.h"

int AVLCompare(const void *data1, const void *data2);
int AVLIsPositive(void *data, void *arg);

int main(void)
{
	avl_t *avl_tree;
	int data1;
	int data2;
	int data3;
	int data4;
	int data5;
	int arg;
	int i;
	
	avl_tree = AVLCreate(AVLCompare);
	
	printf("After creation, is empty? %d\n", AVLIsEmpty(avl_tree));
	printf("After creation, height is: %lu\n", AVLHeight(avl_tree));
	printf("After creation, count is: %lu\n", AVLCount(avl_tree));
	printf("\n");

	data1 = 10;
	data2 = 20;
	data3 = 30;
	data4 = 40;
	data5 = 50;
	assert (AVLInsert(avl_tree, &data1));
	assert (AVLInsert(avl_tree, &data2));
	assert (AVLInsert(avl_tree, &data3));
	assert (AVLInsert(avl_tree, &data4));
	assert (AVLInsert(avl_tree, &data5));

	printf("After insertion, is empty? %d\n", AVLIsEmpty(avl_tree));
	printf("After insertion, height is: %lu\n", AVLHeight(avl_tree));
	printf("After insertion, count is: %lu\n", AVLCount(avl_tree));
	printf("\n");
	
	arg = 0;
	assert (AVLForEach(avl_tree, &AVLIsPositive, &arg));
	
	AVLRemove(avl_tree, &data4);
	printf("After removal, is empty? %d\n", AVLIsEmpty(avl_tree));
	printf("After removal, height is: %lu\n", AVLHeight(avl_tree));
	printf("After removal, count is: %lu\n", AVLCount(avl_tree));
	printf("\n");

/* load test */
	for (i = 0; i < 10000; ++i)
	{
		assert (AVLInsert(avl_tree, &i));
	}
	
	printf("After insertion 10k, is empty? %d\n", AVLIsEmpty(avl_tree));
	printf("After insertion 10k, height is: %lu\n", AVLHeight(avl_tree));
	printf("After insertion 10k, count is: %lu\n", AVLCount(avl_tree));
	printf("\n");

	
	AVLDestroy(avl_tree);

	return (0);
}

int AVLCompare(const void *data1, const void *data2)
{
	return ((data1 > data2) ? 1 : (data1 < data2) ? -1 : 0);
}

int AVLIsPositive(void *data, void *arg)
{
	assert (data && arg);
	
	return (*(int *)data >= *(int *)arg);
}
