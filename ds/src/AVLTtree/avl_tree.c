/*******************************************************************************
Almost every function has one or moore utility functions. These functions can
operate recursivly on a specific node instead of the entire avl tree.

					  		 Written by Anat Wax
						   7-13 of April 3rd, 2020
							Reviewer: Lusy Volkov
*******************************************************************************/
#include <stdlib.h> /* malloc(), free(), size_t */
#include <assert.h> /* assert() */
#include <stdio.h>	/* printf(), size_t */

#include "avl_tree.h"

#define FREE(x) ((free(x), (x = NULL)))

typedef enum
{
	LEFT,	 /* 0 */
	RIGHT,	 /* 1 */
	NUM_SONS /* 2 */
} children_e;

children_e direction;

typedef struct node_s
{
	void *data;
	struct node_s *nodes[2];
	size_t height;
} node_t;

struct AVLTree
{
	node_t *root;
	int (*cmp_func)(const void *first, const void *second);
}; /* avl_t */

/**************************** utiliy funcs: ***********************************/

static int CheckAndPrintTree(node_t *root);

/******************************************************************************/

static node_t *AVLCreateNode(const void *data)
{
	node_t *new_node = NULL;

	assert(data);

	new_node = (node_t *)malloc(sizeof(node_t));

	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->nodes[RIGHT] = NULL;
	new_node->nodes[LEFT] = NULL;
	new_node->data = (void *)data;
	new_node->height = 1;

	return (new_node);
}

/*********************************/

avl_t *AVLCreate(int (*cmp_func)(const void *first, const void *second))
{
	avl_t *tree = NULL;

	assert(cmp_func);

	tree = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->cmp_func = cmp_func;
	tree->root = NULL;

	return (tree);
}

/******************************************************************************/

static void DeleteNode(node_t *current)
{
	if (current == NULL)
	{
		return;
	}

	if (current->nodes[LEFT])
	{
		DeleteNode(current->nodes[LEFT]);
	}

	if (current->nodes[RIGHT])
	{
		DeleteNode(current->nodes[RIGHT]);
	}

	FREE(current);
}

/*********************************/

/* uses post-order */
void AVLDestroy(avl_t *tree)
{
	assert(tree);

	DeleteNode(tree->root);
	FREE(tree);
}

/******************************************************************************/
/*************************** insert utility functions *************************/

static size_t NodeHeight(node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}

	return (node->height);
}

/**************/

static int AVLMaxOfTwo(int first, int second)
{
	return (first > second ? first : second);
}

/**************/

static int AVLGetBalance(node_t *current)
{
	if (NULL == current)
	{
		return (0);
	}

	return (NodeHeight(current->nodes[LEFT]) -
			NodeHeight(current->nodes[RIGHT]));
}

/**************/

static node_t *RotateLeft(node_t *current)
{
	node_t *current_right = current->nodes[RIGHT];
	node_t *next_left = current_right->nodes[LEFT];

	assert(current);
	current_right->nodes[LEFT] = current;
	current->nodes[RIGHT] = next_left;

	current->height = AVLMaxOfTwo(NodeHeight(current->nodes[LEFT]),
								  NodeHeight(current->nodes[RIGHT])) + 1;
	current_right->height = AVLMaxOfTwo(NodeHeight(current_right->nodes[LEFT]),
										NodeHeight(current_right->nodes[RIGHT]))
										+ 1;

	return (current_right);
}

/**************/

static node_t *RotateRight(node_t *current)
{
	node_t *current_left = current->nodes[LEFT];
	node_t *next_right = current_left->nodes[RIGHT];

	assert(current);
	current_left->nodes[RIGHT] = current;
	current->nodes[LEFT] = next_right;

	current->height = AVLMaxOfTwo(NodeHeight(current->nodes[LEFT]),
								  NodeHeight(current->nodes[RIGHT])) + 1;
	current_left->height = AVLMaxOfTwo(NodeHeight(current_left->nodes[LEFT]),
									   NodeHeight(current_left->nodes[RIGHT])) 
									   + 1;

	return (current_left);
}

/**************/

static node_t *AVLBalanceTree(node_t *current)
{
	int balance = 0;

	if (NULL == current)
	{
		return (NULL);
	}

	assert(current);

	current->nodes[LEFT] = AVLBalanceTree(current->nodes[LEFT]);
	current->nodes[RIGHT] = AVLBalanceTree(current->nodes[RIGHT]);

	balance = AVLGetBalance(current);

	/* if node is unbalanced, there are four opptional rotations: */
	/* left-left rotation: */
	if (balance > 1 && 0 <= AVLGetBalance(current->nodes[LEFT]))
	{
		return (RotateRight(current));
	}
	/* left-right rotation: */
	else if (balance > 1 && 0 > AVLGetBalance(current->nodes[LEFT]))
	{
		current->nodes[LEFT] = RotateLeft(current->nodes[LEFT]);
		return (RotateRight(current));
	}
	/* right-right rotation: */
	else if (balance < (-1) && 0 >= AVLGetBalance(current->nodes[RIGHT]))
	{
		return (RotateLeft(current));
	}
	/* right-left rotation: */
	else if (balance < (-1) && 0 > AVLGetBalance(current->nodes[RIGHT]))
	{
		current->nodes[RIGHT] = RotateRight(current->nodes[RIGHT]);
		return (RotateLeft(current));
	}

	current->height = AVLMaxOfTwo(NodeHeight(current->nodes[LEFT]),
								  NodeHeight(current->nodes[RIGHT])) + 1;

	return (current);
}

/*********************************/

static node_t *AVLInsertNode(node_t *current, node_t *new_node, void *data,
							 int (*cmp_func)(const void *first,
							 				 const void *second))
{
	if (NULL == current)
	{
		return (new_node);
	}

	/* if data is smaller than the data in the */
	/* current node -> go LEFT, else go RIGHT  */
	if (0 > cmp_func(data, current->data))
	{
		current->nodes[LEFT] = AVLInsertNode(current->nodes[LEFT],
											 new_node, data, cmp_func);
	}
	else
	{
		current->nodes[RIGHT] = AVLInsertNode(current->nodes[RIGHT],
											  new_node, data, cmp_func);
	}

	current->height = AVLMaxOfTwo(NodeHeight(current->nodes[LEFT]),
								  NodeHeight(current->nodes[RIGHT])) + 1;

	return (current);
}

/*********************************/

int AVLInsert(avl_t *tree, void *data)
{
	node_t *new_node = NULL;

	assert(tree && data);

	new_node = AVLCreateNode(data);

	if (NULL == new_node)
	{
		return (1);
	}

	/* if tree is empty: */
	if (NULL == tree->root)
	{
		tree->root = new_node;
		/*	new_node->height += 1; */
	}
	else
	{
		AVLInsertNode(tree->root, new_node, data, tree->cmp_func);
		tree->root = AVLBalanceTree(tree->root);
	}

	return (0);
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);

	return ((NULL == tree->root));
}

/******************************************************************************/

size_t AVLHeight(const avl_t *tree)
{
	return (NodeHeight(tree->root) - 1);
}

/******************************************************************************/

static node_t *AVLFindNode(node_t *node, void *data,
						   int (*cmp_func)(const void *first,
						   				   const void *second))
{
	if (node == NULL)
	{
		return (NULL);
	}

	if (0 == cmp_func(data, node->data))
	{
		return (node->data);
	}
	else
	{
		if (0 > cmp_func(data, node->data))
		{
			return (AVLFindNode(node->nodes[LEFT], data, cmp_func));
		}
		else if (0 < cmp_func(data, node->data))
		{
			return (AVLFindNode(node->nodes[RIGHT], data, cmp_func));
		}
		else
		{
			return (NULL);
		}
	}
}

/*************************************/

void *AVLFind(const avl_t *tree, const void *data)
{
	node_t *return_node = NULL;

	assert(tree);
	return_node = tree->root;

	if (0 == tree->cmp_func((void *)data, return_node->data))
	{
		return (return_node->data);
	}
	else
	{
		return (AVLFindNode(return_node, (void *)data, tree->cmp_func));
	}
}

/******************************************************************************/

void *AVLGetData(const bst_iter_t iterator)
{
	assert(iterator);

	return (iterator->data);
}

/******************************************************************************/

static size_t CountNodes(node_t *current)
{
	size_t counter = 1;

	if (current->nodes[LEFT])
	{
		counter += CountNodes(current->nodes[LEFT]);
	}

	if (current->nodes[RIGHT])
	{
		counter += CountNodes(current->nodes[RIGHT]);
	}

	return (counter);
}

/*************************************/

/* uses `pre-order' = first the left sub-tree and than the right sub-tree */
size_t AVLCount(const avl_t *tree)
{
	assert(tree);

	/* if tree is empty: */
	if (NULL == tree->root)
	{
		return (0);
	}
	else
	{
		return (CountNodes(tree->root));
	}
}

/******************************************************************************/

/* uses in-order traversal */
int ForEachIterator(node_t *current, avl_operation_t operation, void *arg)
{
	int status = 0;

	if (NULL != current->nodes[LEFT])
	{
		status = ForEachIterator(current->nodes[LEFT], operation, arg);
	}

	operation(current->data, arg);

	if (NULL != current->nodes[RIGHT])
	{
		status = ForEachIterator(current->nodes[RIGHT], operation, arg);
	}

	return (status);
}

int AVLForEach(avl_t *tree, avl_operation_t operation, void *arg)
{
	int status = 0;

	assert(tree && operation && arg);

	status = ForEachIterator(tree->root, operation, arg);
	return (status);
}

/******************************************************************************/

/* left and than right till NULL */
static node_t *FindPrev(node_t *current)
{
	if (NULL == current->nodes[LEFT])
	{
		return (current);
	}
	else
	{
		current = FindPrev(current->nodes[LEFT]);
	}

	return (current);
}

/*****************************/

static node_t *AVLRemoveNode(node_t *current, const void *data,
							 int (*cmp_func)(const void *first,
							 				 const void *second))
{
	node_t *temp = NULL;

	if (NULL == current)
	{
		return (current);
	}
	/* if the data is smaller than current - move LEFT, else - move RIGHT */
	if (0 > cmp_func((void *)data, current->data))
	{
		current->nodes[LEFT] = AVLRemoveNode(current->nodes[LEFT], data,
											 cmp_func);
	}
	else if (0 < cmp_func((void *)data, current->data))
	{
		current->nodes[RIGHT] = AVLRemoveNode(current->nodes[RIGHT], data,
											  cmp_func);
	}
	else
	{
		/* if node is a leaf:*/
		if (NULL == current->nodes[LEFT] && NULL == current->nodes[RIGHT])
		{
			FREE(current);
			return (NULL);
		}
		/* if node has one child - in the LEFT node: */
		else if (NULL == current->nodes[RIGHT])
		{
			temp = current->nodes[LEFT];
			FREE(current);

			return (temp);
		}
		/* if node has one child - in the RIGHT node: */
		else if (NULL == current->nodes[LEFT])
		{
			temp = current->nodes[RIGHT];
			FREE(temp);

			return (temp);
		}
		/* if node has two children: */
		else
		{
			temp = FindPrev(current->nodes[RIGHT]);

			current->data = temp->data;
			current->nodes[RIGHT] = AVLRemoveNode(current->nodes[RIGHT],
												  temp->data, cmp_func);
		}
	}

	return (current);
}

/*****************************/

void AVLRemove(avl_t *tree, const void *data)
{
	node_t *temp = NULL;

	/* if removing the root - update the struct manager: */
	if (0 == tree->cmp_func(tree->root->data, data))
	{
		temp = AVLRemoveNode(tree->root, data, tree->cmp_func);
		tree->root = temp;
	}
	else
	{
		AVLRemoveNode(tree->root, data, tree->cmp_func);
	}

	tree->root = AVLBalanceTree(tree->root);
}

/***************************** utility funcs **********************************/

void InOrderTraversalPrint(avl_t *tree)
{
	if (!tree->root)
	{
		printf("Empty tree!\n");
		return;
	}

	CheckAndPrintTree(tree->root);
}

/*****************************/

static int CheckAndPrintTree(node_t *root)
{
	/* in order traverse and check that each element is greater than the */
	/* one before 														 */

	if (root->nodes[LEFT] != NULL)
	{
		assert(*(int *)root->data > CheckAndPrintTree(root->nodes[LEFT]));
	}

	printf("%d, height %lu\n", *(int *)root->data, root->height - 1);

	if (root->nodes[RIGHT] != NULL)
	{
		assert(*(int *)root->data < CheckAndPrintTree(root->nodes[RIGHT]));
	}

	return (*(int *)root->data);
}