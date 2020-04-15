/*******************************************************************************
					  		 Written by Anat Wax
						   7-13 of April 3rd, 2020
							Reviewer: Lusy Volkov
*******************************************************************************/
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h> /* size_t */

typedef int (*avl_operation_t)(void *data, void *arg);
typedef struct AVLTree avl_t;
typedef struct node_s *bst_iter_t;

/*
* Receive: cmp_func:
*          Recieve: data1, data2 - data to compare.
*                   param - parameter for the function to work with.
*          Return: 1 if data1 is bigger than data2.
*                  0 if they are equal.
*                  -1 if data2 is smaller than data1.
*		   param - the parameter cpm_func recieve is given again seperatly for
*		   		   use within the function.
* Return: pointer to avl_t managing struct.
* Errors: return NULL if error occured.
* Time Complexity: O(1)
*/
avl_t *AVLCreate(int (*cmp_func)(const void *first,const void *second));

/* 
 * Function that delete all argument and free all relevant data of the tree.
 * Arguments: tree - pointer to bst_t tree.
 * Compexity: O(n)
 */
void AVLDestroy(avl_t *tree);

/*
 * Insert new element into the tree.
 * Arguments: tree - pointer to bst_t tree.
 *          data - pointer to data. the tree does NOT support equal nodes.
 * 				   Equal nodes Insert will result in an undefined behavior. 
 * Return: 0 if successed, 1 - if an error has occured.
 * Compexity: O(log n)
 */
int AVLInsert(avl_t *tree, void *data);

/*
 * Remove an element from the tree.
 * Arguments: tree - tha AVL tree to remove data from.
 * 			  data - pointer to the data to remove from tree.
 * Compexity: O(log n)
 */
void AVLRemove(avl_t *tree, const void *data);

/* 
 * Get tree's size.
 * Arguments: tree - pointer to avl_t tree.
 * Return: size_t with tree's size.
 * Compexity: O(n)
 */
size_t AVLCount(const avl_t *tree);

/*
 * Check if tree is empty.
 * Arguments: tree - pointer to avl_t tree.
 * Return: 1 if empty, 0 if not.
 * Compexity: O(1)
 */
int AVLIsEmpty(const avl_t *tree);

/* 
 * Commit operation on each list element.
 * Arguments: tree - pointer to the avl_t tree to commit changes on.
 *            operation:
 *                     Recieve: data - to commit operation on.
 *                              param - parameter for the function to work with.
 *                     Return: 0 to continue actions, any other number if not.
 *             arg - parameter for the function to work with.
 * Return: 0 if operation committed successfuly on all the elements in the tree;
 *         any other value: value returned from opr_func.
 * Time Complexity: O(n)
 */
int AVLForEach(avl_t *tree, avl_operation_t operation, void *arg);

/*
 * Get the current higest hight from root to leaf.
 * Return: highest hight of the tree from root to leaf.
 * Arguments: pointer to avl_t tree.
 * Compexity: O(log n)
 */
size_t AVLHeight(const avl_t *tree);

/*
 * Find Element in avl tree.
 * Arguments: tree - pointer to avl_t tree.
 *            data - data to search.
 * Return: if found - pointer the data found. If couldn't find - returns NULL.
 * Complexity: O(log n)
 */
void *AVLFind(const avl_t *tree, const void *data);

/************************ utility funcions: ************************/

void *AVLGetData(const bst_iter_t iterator);

void InOrderTraversalPrint(avl_t *tree);

#endif /* AVL_TREE_H */