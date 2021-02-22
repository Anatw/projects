/*******************************************************************************
					  		 Written by Anat Wax
						  March 31 - April 3rd, 2020
							 Reviewer: Amir Paz
*******************************************************************************/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stddef.h> /* size_t */

/* Doubly Linked List type */
typedef struct binary_search_tree bst_t;
typedef struct bst_node *bst_iter_t;

bst_iter_t BSTGetRoot(bst_t *tree);

/*
* Binary Search Tree Create: Create BST
* Receive: cmp_func:
*          Recieve: data1, data2 - data to compare.
*                   param - parameter for the function to work with.
*        * Return: 1 if data1 is bigger than data2.
*                  0 if they are equal.
*                  -1 if data2 is smaller than data1.
		   param - the parameter cpm_func recieve is given again seperatly for
		   		   use within the function.
* Return: pointer to bst_t managing struct.
* Errors: return NULL if error occured.
* Time Complexity: O(1)
*/
bst_t *BSTCreate(int (*cmp_func)(const void *data1, const void *data2,
				 const void *param), const void *param);

/*
* Binary Search Tree Destroy: Destroy BST
* Receive: tree - pointer to bst_t tree.
* Time Complexity: O(n)
*/
void BSTDestroy(bst_t *tree);

/*
* Binary Search Tree Insert: Insert new element into the tree.
* Receive: tree - pointer to bst_t tree.
*          data - pointer to data.
* Return: bst_iter_t iterator at the element inserted.
* Errors: return iterator that equal to BSTEnd if error occured.
* Time Complexity: O(log n)
*/
bst_iter_t BSTInsert(bst_t *tree, const void *data); /* return at error? NULL iterator that is equal to BSTEnd */

/*
* Binary Search Tree Remove: Remove element from the tree.
* Receive: iterator - at the element to remove.
* Time Complexity: O(1)
*/
void BSTRemove(bst_iter_t iterator);

/*
* Binary Search Tree Get Data: Get data from an iterator.
* Receive: iterator - at the element to get data from.
* Return: data - pointer to void.
* Time Complexity: O(1)
*/
void *BSTGetData(const bst_iter_t iterator);

/*
* Binary Search Tree Begin: Get iterator at the root of the tree.
* Receive: tree - pointer to bst_t tree.
* Return: bst_iter_t - the iterator with the smallest value within the tree.
* Comment: when the tree is empty, BSTBegin is at BSTEnd.
* Time Complexity: O(log n)
*/
bst_iter_t BSTBegin(const bst_t *tree);

/*
* Binary Search Tree End: Get iterator at the end of the tree.
* Receive: tree - pointer to bst_t tree.
* Return: bst_iter_t iterator at the end of the tree.
* Comment: this is a stub iterator - its data is undefined. the last element.
*          inserted by user is its previous iterator.
* Time Complexity: O(log n)
*/
bst_iter_t BSTEnd(const bst_t *tree); /* return NULL iterator */

/*
* Binary Search Tree Next: Get next iterator.
* Receive: iterator - at the element to get its next.
* Return: bst_iter_t iterator at the next element. If iterator given is the one
		  eith the biggest data in the tree - the function eill return the root.
* Time Complexity: O(log n)
*/
bst_iter_t BSTNext(const bst_iter_t iterator);

/*
* Binary Search Tree Previous: Get previous iterator. If request the value
* previous to the smallest value - undefined behavior.
* Receive: iterator - at the element to get its previous.
* Return: bst_iter_t iterator at the previous element. If iterator given by the
		  the user is the root - function will return an iterator to the 
		  iterator with the biggest data in the tree.
* Time Complexity: O(log n)
*/
bst_iter_t BSTPrev(const bst_iter_t iterator);

/*
* Binary Search Tree Is Equal: Check if 2 iterators are the same.
* Receive: iter1 & iter2 - to check if equal.
* Return: 1 if equal, 0 if not.
* Time Complexity: O(1)
*/
int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2);

/*
* Binary Search Tree Size: Get tree's size.
* Receive: tree - pointer to bst_t tree.
* Return: size_t with tree's size.
* Time Complexity: O(n)
*/
size_t BSTSize(const bst_t *tree);

/*
* Binary Search Tree Is Empty: Check if tree is empty.
* Receive: tree - pointer to bst_t tree.
* Return: 1 if empty, 0 if not.
* Time Complexity: O(1)
*/
int BSTIsEmpty(const bst_t *tree);

/*
* Binary Search Tree Find: Find Element in BST using cmp_func provided in 
*                          BSTCreate.
* Receive: tree - pointer to bst_t tree.
*          data - data to search.
* Return: iterator at the element if found, iterator that is equal to BSTEnd if 
*         not found.
* Time Complexity: O(log n)
*/
bst_iter_t BSTFind(bst_t *tree, const void *data);

/*
* Binary Search Tree For Each: Commit operation on each list element.
* Receive: from - iterator to start from.
*          to - iterator to stop at (exclusive!).
*          opr_func:
*                   Recieve: data - to commit operation on.
*                            param - parameter for the function to work with.
*                   Return: 0 to continue actions, any other number if not.
*          param - parameter for the function to work with.
* Return: 0 if operation committed successfuly on all the elements in the tree;
*         any other value: value returned from opr_func.
* Time Complexity: O(n)
*/
int BSTForEach(const bst_iter_t from,
               const bst_iter_t to,
               int (*opr_func)(const void *data, const void *param),
               const void *param);

/******************************************/

/* Depth = the number of edges in a path between a leaf and the root.
Hight of a leaf is 0. 
   Complexity: O(n)*/
size_t MaxDepth(const bst_iter_t root);


#endif /* BINARY_STREE_H */
