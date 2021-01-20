#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /*assert() */
#include <time.h> /* time, size_t, srand() */

#include "avl_tree.h"

#define ARRAY_SIZE (50)

int AVLcmp_func(const void *first, const void *second);

int operation(void *data, void *arg);

void CreateRandomArray(int *arr, int size, const int lower, const int upper);

int main()
{
	avl_t *tree = AVLCreate(AVLcmp_func);
	int data1 = 5;
	int data2 = 4;
	int data3 = 7;
	int data4 = 2;
	int data5 = 1;
	int arg = 2;
	size_t index = 0;
	int *node = NULL;
	
	/*int *array[ARRAY_SIZE] = {0};
	 CreateRandomArray(array, ARRAY_SIZE, 0, RAND_MAX); */
	
	printf("the tree is%s empty\n", (AVLIsEmpty(tree) ? " not" : ""));
	
	for (; index < ARRAY_SIZE; ++index)
	{
		node = (int *)malloc(sizeof(int));
		*node = rand() % 100;
		AVLInsert(tree, node);
	}
	/*
	AVLInsert(tree, &data1);
	AVLInsert(tree, &data2);
	AVLInsert(tree, &data3);
	AVLInsert(tree, &data4);
	AVLInsert(tree, &data5);*/
	
	InOrderTraversalPrint(tree);
	printf("number of nodes in tree: %ld\n", AVLCount(tree));
	printf("current hight of the root is: %ld\n", AVLHeight(tree));
	printf("the tree is%s empty\n", (AVLIsEmpty(tree) ? " not" : ""));
	
	printf("searching for 4...\n");
	printf("found: %d\n", *(int *)AVLFind(tree, &data2));
	
	printf("number of nodes in tree: %ld\n", AVLCount(tree));
	
	AVLForEach(tree, operation, &arg);
	InOrderTraversalPrint(tree);
	
	AVLRemove(tree, &data1);
	AVLRemove(tree, &data3);
	AVLRemove(tree, &data2);

	printf("number of nodes in tree: %ld\n", AVLCount(tree));

	AVLDestroy(tree);
	
	return (0);
}


/* returns 1 if should go RIGHT and -1 if should go LEFT, 0 if equal */
int AVLcmp_func(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
	{
		return (1);
	}
	else if (*(int *)first < *(int *)second)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}

int operation(void *data, void *arg)
{
	*(int *)data *= *(int *)arg;
	
	return (0);
}

void CreateRandomArray(int *array, int size, const int lower, const int upper)
{
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{	
		array[i] = (rand() % (upper - lower + 1)) + lower;
	}
}

/* from dean:
void CreateRandomArray(int *arr, int size, const int lower, const int upper)
{
	int i = 0;
	int index_size = upper - lower + 1;
	
	int *check = (int *)malloc(index_size * sizeof(int));
	
	srand (time(NULL));
	
	for (i = 0; i < size; ++i)
	{	
		arr[i] = (rand() % (upper - lower + 1)) + lower;
		
		while (check[arr[i]] == 1)
		{
			arr[i] = (rand() % (upper - lower + 1)) + lower;			
		}
		
		check[arr[i]] = 1;
	}
}*/
