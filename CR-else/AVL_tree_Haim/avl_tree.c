/*******************************************************************************

File: avltree.c
Purpose: functions to implement AVL Tree
Date: April 2020
Author: Haim Saadia
Reviewer: Anat Wax

*******************************************************************************/

#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */

#include "avl_tree.h"

#define BIGGER(a,b) ((a > b) ? a : b)

typedef enum
{
	LEFT,
	RIGHT,
	NUM_SONS
} children_e;

typedef struct node_s
{
	void *data;
	struct node_s *children[NUM_SONS];
	size_t height;
} node_t;

struct AVLTree
{
	node_t *root;
	int (*cmp_func)(const void *data1, const void *data2);
};

/******************************************************************************/

/* Declarations of utility functions: */

/*
Purpose: create a new node
Return: pointer to the new node
Recieve: data for the new node
Complexity: O(1)
*/
node_t *AVLCreateNode(const void *data);

/*
Purpose: Insert node to into place in avl_tree
Recieve:1. parent node
		2. child node
		3. compare function of the avl_tree:
			Purpose: compare 2 datas
			Return: 1 if data1 is bigger, -1 if smaller and 0 if equal to data2
			Complexity: O(1)
Complexity: O(log(n))
*/
void AVLInsertNewNode(node_t *root, node_t *node, 
					int (*cmp_func)(const void *data1, const void *data2));

/*
Purpose: Find a node by data
Return: pointer to node
Recieve:1. node to compare its data
		2. requested data
		3. compare function of avl_tree
Complexity: O(log(n))
*/
void *AVLTraverseFind(node_t *node, void *data, 
					int (*cmp_func)(const void *data1, const void *data2));

/*
Purpose: Count number of nodes in avl_tree recursively
Return: number of nodes
Recieve: node
Complexity: O(n)
*/
size_t AVLCountPreOrder(node_t *node);

/*
Purpose: operate a function on each node in avl_tree
Return: status: 0 for success, 1 for failure
Recieve:1. node to be operate on
		2. poiter to operation function
		3. argument for the operation function
Complexity: O(n)
*/
int AVLInOrderForEach(node_t *node, avl_operation_t operation, void *arg);

/*
Purpose: free alocated memory of each node in avl_tree recursively
Recieve: node to free
Complexity: O(n)
*/
void *AVLPostOrderDestroy(node_t *node);

/*
Purpose: Finds node to delete and deletes it with help of successor
Return: the successor node
Recieve:1. node to check and deleted
		2. data to find
Complexity: O(log(n))
*/
node_t *AVLSearchAndDelete(node_t *node, int data);

/*
Purpose: find a successor node recursively to help the delete function
Return: pointer to the successor node
Recieve: node
Complexity: O(n)
*/
node_t *AVLFindSuccessor(node_t *node);

/*
Purpose: balance the tree after insertion or removal
Recieve: node
Complexity: O(log(n))
*/
node_t *AVLBalanceIfNeeded(node_t *root,
					   int (*cmp_func)(const void *data1, const void *data2));

/*
Purpose: utility function to check the height of subtree
Return: height of subtree
Recieve: node
Complexity: O(1)
*/
size_t AVLNodeHeight(node_t *node);

/*
Purpose: balance the tree from right side
Return: pointer to the balanced node
Recieve: un-balanced node
Complexity: O(1)
*/
node_t *AVLRightRotate(node_t *node);

/*
Purpose: balance the tree from left side
Return: pointer to the balanced node
Recieve: un-balanced node
Complexity: O(1)
*/
node_t *AVLLeftRotate(node_t *node);

/*
Purpose: get the balance of a node
Return: balance of node
Recieve: node
Complexity: O(1)
*/
int AVLGetBalance(node_t *node);

/******************************************************************************/

avl_t *AVLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	avl_t *new_avl;
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if(!new_avl)
	{
		return (NULL);
	}
	
	new_avl->root = NULL;
	
	new_avl->cmp_func = cmp_func;
	
	return (new_avl);
}

/******************************************************************************/

void AVLDestroy(avl_t *tree)
{
	assert (tree);
	
	AVLPostOrderDestroy(tree->root);
	
	free(tree);
	tree = NULL;
}

/******************************************************************************/

int AVLInsert(avl_t *tree, void *data)
{
	node_t *new_node;
	
	assert (tree && data);
	
	new_node = AVLCreateNode(data);
	if (!new_node)
	{
		return (0);
	}

	if (AVLIsEmpty(tree))
	{
		tree->root = new_node;
	}
	else
	{
		AVLInsertNewNode(tree->root, new_node, tree->cmp_func);
		
		tree->root = AVLBalanceIfNeeded(tree->root, tree->cmp_func);
	}

	return (1);
}

/******************************************************************************/

void AVLRemove(avl_t *tree, const void *data)
{
	assert (tree && data);

	AVLSearchAndDelete(tree->root, *(int *)data);
	
	tree->root = AVLBalanceIfNeeded(tree->root, tree->cmp_func);
}

/******************************************************************************/

size_t AVLCount(const avl_t *tree)
{
	assert(tree);
	
	return (AVLCountPreOrder(tree->root));
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *tree)
{
	assert (tree);

	return (NULL == tree->root);
}

/******************************************************************************/

int AVLForEach(avl_t *tree, avl_operation_t operation, void *arg)
{
	assert (tree);
	
	return (AVLInOrderForEach(tree->root, operation, arg));
}

/******************************************************************************/

size_t AVLHeight(const avl_t *tree)
{
	assert (tree);
	
	return ((AVLIsEmpty(tree)) ? 0 : tree->root->height);
}

/******************************************************************************/

void *AVLFind(const avl_t *tree, const void *data)
{
	assert (tree && data);
	
	return ((AVLIsEmpty(tree)) ? tree->root : 
	AVLTraverseFind(tree->root, (void *)data, tree->cmp_func));
}

/******************************************************************************/


/********** Utility functions: **********/

node_t *AVLCreateNode(const void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof (node_t));
	if(!new_node)
	{
		return (NULL);
	}
	
	new_node->data = (void *)data;
	new_node->height = 1;
	new_node->children[RIGHT] = NULL;
	new_node->children[LEFT] = NULL;

	return (new_node);
}

/******************************************************************************/

void AVLInsertNewNode(node_t *root, node_t *node, 
					int (*cmp_func)(const void *data1, const void *data2))
{
	assert (root && node && cmp_func);

	if (cmp_func(node->data, root->data) > 0)
	{
		if(root->children[RIGHT])
		{
			AVLInsertNewNode(root->children[RIGHT], node, cmp_func);
		}
		else
		{
			root->children[RIGHT] = node;
		}
	}
	else
	{
		if(root->children[LEFT])
		{
			AVLInsertNewNode(root->children[LEFT], node, cmp_func);
		}
		else
		{
			root->children[LEFT] = node;
		}
	}
}

/******************************************************************************/

void *AVLTraverseFind(node_t *node, void *data, 
					int (*cmp_func)(const void *data1, const void *data2))
{
	return ((!node || node->data == data) ? node :
	(cmp_func(data, node->data) > 0) ? 
	AVLTraverseFind(node->children[RIGHT], data, cmp_func) :
	AVLTraverseFind(node->children[LEFT], data, cmp_func));
}

/******************************************************************************/

size_t AVLCountPreOrder(node_t *node)
{
	return ((!node) ? 0 : 1 + AVLCountPreOrder(node->children[LEFT]) +
	AVLCountPreOrder(node->children[RIGHT]));
}

/******************************************************************************/

int AVLInOrderForEach(node_t *node, avl_operation_t operation, void *arg)
{
	return ((NULL == node) ? 0 : 
	AVLInOrderForEach(node->children[LEFT], operation, arg) + 
	operation(node->data, arg) +
	AVLInOrderForEach(node->children[RIGHT], operation, arg));
}

/******************************************************************************/

void *AVLPostOrderDestroy(node_t *node)
{
	if (NULL != node)
	{
		free(AVLPostOrderDestroy(node->children[LEFT]));
		node->children[LEFT] = NULL;
		
		free(AVLPostOrderDestroy(node->children[RIGHT]));
		node->children[RIGHT] = NULL;
		
		free(node);
		node = NULL;
	}

	return (NULL);
}

/******************************************************************************/

node_t *AVLSearchAndDelete(node_t *node, int data)
{
    node_t *succ;  
    node_t *succParent;
    node_t *temp;
        
    /* Base case */
    if (node == NULL)
    {
        return (node);
  	}
  	
    /* Recursive calls for ancestors of node to be deleted */
    if (*(int *)node->data > data)
    {
        node->children[LEFT] = AVLSearchAndDelete(node->children[LEFT], data);

        return (node);
    } 
    else if (*(int *)node->data < data)
    { 
        node->children[RIGHT] = AVLSearchAndDelete(node->children[RIGHT], data);

        return (node);
    } 
  
    /* We reach here when node is the node to be deleted. */

    /* If one of the children is empty */
    else if (node->children[LEFT] == NULL)
    {
        temp = node->children[RIGHT]; 
        free(node);
        return (temp);
    } 
    else if (node->children[RIGHT] == NULL)
    {
        temp = node->children[LEFT]; 
        free (node);
        return (temp);
    } 
  
    /* If both children exist */
    else
    {
        succParent = node;
        succ = AVLFindSuccessor(node->children[RIGHT]);
  
        /* Delete successor. Since successor is always left child of its parent 
           we can safely make successor's right child as left of its parent. 
           If there is no succ, then assign succ->right to succParent->right */
           
        if (succParent != node) 
        {
            succParent->children[LEFT] = succ->children[RIGHT];
        }
        else
        {
            succParent->children[RIGHT] = succ->children[RIGHT]; 
  		}
  		
        /* Copy Successor Data to node */
        node->data = succ->data; 
  
        /* Delete Successor and return node */
        free (succ);          
        return node; 
    } 
}

/******************************************************************************/

node_t *AVLFindSuccessor(node_t *node)
{
	assert (node);
	
	return ((NULL == node->children[LEFT]) ? node : 
	AVLFindSuccessor(node->children[LEFT]));
}

/******************************************************************************/

size_t AVLNodeHeight(node_t *node)
{
	return ((NULL == node) ? 0 : node->height);
}

/******************************************************************************/

node_t *AVLRightRotate(node_t *node)
{
	node_t *left_node = node->children[LEFT];
	node_t *right_of_left = left_node->children[RIGHT];
	
	left_node->children[RIGHT] = node;
	node->children[LEFT] = right_of_left;
	
	node->height = 1 + BIGGER(AVLNodeHeight(node->children[LEFT]),
								AVLNodeHeight(node->children[RIGHT]));
	left_node->height = 1 + BIGGER(AVLNodeHeight(left_node->children[LEFT]),
								AVLNodeHeight(left_node->children[RIGHT]));
								
	return (left_node);
}

/******************************************************************************/

node_t *AVLLeftRotate(node_t *node)
{
	node_t *right_node = node->children[RIGHT];
	node_t *left_of_right = right_node->children[LEFT];
	
	right_node->children[LEFT] = node;
	node->children[RIGHT] = left_of_right;
	
	node->height = 1 + BIGGER(AVLNodeHeight(node->children[LEFT]),
								AVLNodeHeight(node->children[RIGHT]));
	right_node->height = 1 + BIGGER(AVLNodeHeight(right_node->children[LEFT]),
								AVLNodeHeight(right_node->children[RIGHT]));
								
	return (right_node);
}

/******************************************************************************/

int AVLGetBalance(node_t *node)
{
	return ((NULL == node) ? 0 : AVLNodeHeight(node->children[LEFT]) - 
					AVLNodeHeight(node->children[RIGHT]));
}

/******************************************************************************/

node_t *AVLBalanceIfNeeded(node_t *root,
					   int (*cmp_func)(const void *data1, const void *data2))
{
	int balance = 0;

	if (root == NULL)
	{
		return (NULL);
	}

	root->children[LEFT] = AVLBalanceIfNeeded(root->children[LEFT], cmp_func);
	root->children[RIGHT] = AVLBalanceIfNeeded(root->children[RIGHT], cmp_func);

	balance = AVLGetBalance(root);

	if (balance > 1 && AVLGetBalance(root->children[LEFT]) >= 0)
	{
		return (AVLRightRotate(root));
	}
	if (balance < -1 && AVLGetBalance(root->children[RIGHT]) <= 0)
	{
		return (AVLLeftRotate(root));
	}
	if (balance > 1 && AVLGetBalance(root->children[LEFT]) < 0)
	{
		root->children[LEFT] = AVLLeftRotate(root->children[LEFT]);
		
		return (AVLRightRotate(root));
	}
	if (balance < -1 && AVLGetBalance(root->children[RIGHT]) > 0)
	{
		root->children[RIGHT] = AVLRightRotate(root->children[RIGHT]);
		
		return (AVLLeftRotate(root));
	}

	root->height = 1 + BIGGER(AVLNodeHeight(root->children[LEFT]), 
								AVLNodeHeight(root->children[RIGHT]));

	return (root);
}
