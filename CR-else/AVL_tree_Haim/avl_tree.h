/*******************************************************************************

File: avltree.h
Purpose: header file for the functions to implement AVL Tree
Date: April 2020
Author: Haim Saadia
Reviewer: Anat Wax

*******************************************************************************/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <unistd.h>	/* size_t */

typedef struct AVLTree avl_t;
typedef int (*avl_operation_t) (void *data, void *arg);

/*
Purpose: create an avl tree
Return: pointer to the new avl tree
Recieve: compare function:
			Return: status -  1 if first is bigger than second
							  0 if first is equal to second
							 -1 if first is smaller than second		
			Recieve: 2 datas to be compered
			Complexity: O(1)
Complexity: O(1)
*/
avl_t *AVLCreate(int (*cmp_func)(const void *data1, const void *data2));

/*
Purpose: free the allocated memory of the avl tree
Recieve: avl tree
Complexity: O(1)
*/
void AVLDestroy(avl_t *tree);

/*
Purpose: insert data to the avl tree
Return: status - 1 for success, 0 for failure
Recieve: avl tree, and a data to insert
Complexity: O(log(n))
*/
int AVLInsert(avl_t *tree, void *data);

/*
Purpose: delete data from avl tree
Recieve: avl tree, and the data to be removed
Complexity: O(log(n))
*/
void AVLRemove(avl_t *tree, const void *data);

/*
Purpose: count the number of nodes in the avl tree
Return: number of nodes
Recieve: avl tree
Complexity: O(n)
*/
size_t AVLCount(const avl_t *tree);

/*
Purpose: check if avl tree is empty
Return: status - 1 if empty, 0 if not
Recieve: avl tree
Complexity: O(1)
*/
int AVLIsEmpty(const avl_t *tree);

/*
Purpose: operate on each node in avl tree
Return: status - 0 for success, 1 for failure
Recieve:1. avl tree
		2. pointer of operation function:
				Return: status - 0 for success, 1 for failure
				Recieve: 2 datas to operate on 
		3. argument to operate with
Complexity: O(n)
*/
int AVLForEach(avl_t *tree, avl_operation_t operation, void *arg);

/*
Purpose: Get the height of avl tree
Return: height of avl tree
Recieve: avl tree
Complexity: O(1)
*/
size_t AVLHeight(const avl_t *tree);

/*
Purpose: search for data in avl tree
Return: pointer to data, or NULL if not found (not exist)
Recieve: avl tree, and data to look for
Complexity: O(log(n))
*/
void *AVLFind(const avl_t *tree, const void *data);


#endif /* AVL_TREE_H */
