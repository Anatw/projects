/*******************************************************************************
					  		 Written by Anat Wax
						  March 31 - April 3rd, 2020
							 Reviewer: Amir Paz
*******************************************************************************/

#include <stdlib.h> /* size_t */
#include <assert.h> /* assert() */
#ifndef NDEBUG
#include <stdio.h> /* printf() */
#endif

#include "binary_search_tree.h"
#include "stack.h"

#define FREE(x) ((free(x), (x = NULL)))
#define STACK_SIZE (1000)
#define IS_LEFT_CHILD(current) (current->parent->nodes[LEFT] == current)
#define IS_RIGHT_CHILD(current) (current->parent->nodes[RIGHT] == current)
#define IS_CHILDLESS(current) (!IS_LEFT_CHILD(current) && \
							   !IS_RIGHT_CHILD(current))
#define IS_STUB(current) (NULL == current->parent->parent)

typedef enum
{
	LEFT, 	 /* 0 */
	RIGHT,   /* 1 */
	NUM_SONS /* 2 */
} children_e;

children_e direction;

typedef struct bst_node
{
	struct bst_node *parent;
	struct bst_node *nodes[2];
	void *data;
} bst_node_t; /* *bst_iter_t */

/******************************************************************************/

struct binary_search_tree
{
	bst_node_t root_stub;
	int (*cmp_func)(const void *data1, const void *data2, const void *param);
	void *param;
}; /* bst_t */

/************************** utility functions: ********************************/
/* function to check if a certain iterator has left (returns 0) or right 
 * (returns 1) child) 
 */
int BSTHasLeftOrRightChild(const bst_iter_t iterator)
{
	return (iterator->nodes[RIGHT] ? 1 : 0);
}
/* function to check if a certain iterator is a leaf (childless) */ 
int BSTIsChildless(const bst_iter_t iterator)
{
	return ((!iterator->nodes[RIGHT] && !iterator->nodes[LEFT]) ? 1 : 0);
}
/* function that returns the iterator of the root (the stub)  */ 
bst_iter_t BSTGetRoot(bst_t *tree)
{
	return (tree->root_stub.nodes[RIGHT]);
}

/******************************************************************************/

bst_t *BSTCreate(int (*cmp_func)
				(const void *data1, const void *data2, const void *param),
				const void *param)
{
	bst_t *tree = NULL;
	void *new_param = (void *)param;
	
	assert(cmp_func);
	tree = (bst_t *)malloc(sizeof(bst_t));
	
	if (NULL == tree)
	{
		return NULL;
	}
	
	tree->cmp_func = cmp_func;
	tree->param = new_param;
	tree->root_stub.parent = NULL;
	tree->root_stub.nodes[RIGHT] = NULL; /* = &tree->root_stub */
	tree->root_stub.nodes[LEFT] = NULL;
	tree->root_stub.data = NULL;
	
	return (tree);
}

/******************************************************************************/

int BSTForEach(const bst_iter_t from,
               const bst_iter_t to,
               int (*opr_func)(const void *data, const void *param),
               const void *param)
{
	bst_node_t *iterator = NULL;
	int status = 0;
	
	assert(opr_func);

	for (iterator = from; iterator != to; iterator = BSTNext(iterator))
	{
		status = opr_func(BSTGetData(iterator), param);
		
		if (0 != status)
		{
			return (1);
		}
	}
	
	return (0);
}

/********************** helping function for destroy **************************/

void BSTPushAllElementsToStack(bst_t *tree, stack_t *stack)
{
	bst_node_t *iterator = NULL;
	
	assert(tree);
	assert(stack);

	for (iterator = BSTBegin(tree);
		 iterator != BSTEnd(tree);
		 iterator = BSTNext(iterator))
	{
		StackPush(iterator, stack);
		#ifndef NDEBUG
	/*	printf("pushed to stack: %d", *(int *)BSTGetData(iterator));*/
		#endif
	}
}

/************************************/

/* destroy iterate the tree in "post-order" form */
void BSTDestroy(bst_t *tree)
{
	stack_t *stack = NULL;
	bst_node_t *iterator = NULL;
	
	assert(tree);
	stack = StackCreate(STACK_SIZE);
	
	if (NULL == stack)
	{
		assert(stack != NULL); /* what should we actually return?? */
	}
	
	BSTPushAllElementsToStack(tree, stack);
	
	while (1 != StackIsEmpty(stack))
	{
		iterator = (bst_node_t *)StackPeek(stack);
		FREE(iterator);
		StackPop(stack);
	}
	
	StackDestroy(stack);
	FREE(tree);
}

/*********************** helping function for insert **************************/

static bst_iter_t BSTCreateNode(const void *data)
{
	bst_node_t *new_node = NULL;
	void *new_data = (void *)data;
	
	assert(data);
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	if (NULL == new_node)
	{
		return (NULL);
	}
	
	new_node->nodes[RIGHT] = NULL;
	new_node->nodes[LEFT] = NULL;
	new_node->data = new_data;
	
	return (new_node);
}

/************************************/

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_node_t *last_node = NULL;
	bst_node_t *next_node = NULL;
	bst_node_t *new_node = NULL;
		
	assert(tree);
	assert(data);
	last_node = &tree->root_stub;
	direction = RIGHT;
	next_node = last_node->nodes[direction];
	
	new_node = BSTCreateNode((void *)data);
	
	if (NULL == new_node)
	{
		return (last_node);
	}
	
	while (NULL != next_node)
	{
		last_node = next_node;
		
		if (0 > tree->cmp_func((void *)data, next_node->data, tree->param))
		{
			direction = LEFT;
		}
		else
		{
			direction = RIGHT;
		}
		
		next_node = next_node->nodes[direction];
	}
	
	last_node->nodes[direction] = new_node;
	new_node->parent = last_node;
	
	return (new_node);
}

/******************************************************************************/

void BSTRemove(bst_iter_t iterator)
{
	bst_node_t *substitute_node = NULL;
	bst_node_t *parent_node = NULL;

	assert(iterator);
	parent_node = iterator->parent;
	direction = (IS_RIGHT_CHILD(iterator) ? 1 : 0);
	
	/* iterator is childless */
	if (NULL == iterator->nodes[RIGHT] && NULL == iterator->nodes[LEFT])
	{
		if (IS_RIGHT_CHILD(iterator))
		{
			iterator->parent->nodes[RIGHT] = NULL;
		}
		else
		{
			iterator->parent->nodes[LEFT] = NULL;
		}
		
		FREE(iterator);
	}
	/* if iterator has two children */
	else if (iterator->nodes[RIGHT] && iterator->nodes[LEFT])
	{
		substitute_node = iterator->nodes[LEFT];
		
		if (NULL == substitute_node->nodes[RIGHT])
		{
			/* connect substitute_node to parent */
			parent_node->nodes[IS_RIGHT_CHILD(iterator)] = substitute_node;
			substitute_node->parent = iterator->parent;
			
			/* connect RIGHT child to substitute_node */
			iterator->nodes[RIGHT]->parent = substitute_node;
			substitute_node->nodes[RIGHT] = iterator->nodes[RIGHT];
		}
		else
		{
			substitute_node = BSTPrev(iterator);
				
			substitute_node->parent->nodes[RIGHT] = substitute_node->nodes[LEFT];
			iterator->nodes[LEFT]->parent = substitute_node;
			
			/* connect substitute_node to parent */
			iterator->parent->nodes[IS_RIGHT_CHILD(iterator)] = substitute_node;
			substitute_node->parent = iterator->parent;
			
			/* connect children to substitute_node */
			substitute_node->nodes[RIGHT] = iterator->nodes[RIGHT];
			substitute_node->nodes[LEFT] = substitute_node;
		}
		
		FREE(iterator);
	}
	/* if iterator has one child - enter data from child to parent */
	else
	{
		if (NULL != iterator->nodes[LEFT])
		{
			substitute_node = iterator->nodes[LEFT];
			iterator->parent->nodes[IS_RIGHT_CHILD(iterator)] = substitute_node;
		}
		else
		{
			substitute_node = iterator->nodes[RIGHT];
			iterator->parent->nodes[IS_RIGHT_CHILD(iterator)] = substitute_node;
		}
		
		substitute_node->parent = parent_node;
		
		FREE(iterator);
	}
}

/******************************************************************************/

void *BSTGetData(const bst_iter_t iterator)
{
	assert(iterator);
	
	return (iterator->data);	
}

/******************************************************************************/

int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{
	assert (itera1 && iter2);
	
	return (iter1 == iter2);
}

/******************************************************************************/

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_node_t *next_node = NULL;
	bst_t *new_tree = (bst_t *)tree;
	
	assert(tree);
	next_node = new_tree->root_stub.nodes[RIGHT];
	
	/* if tree is empty */
	if (NULL == new_tree->root_stub.nodes[RIGHT])
	{
		return (&new_tree->root_stub);
	}
	
	while (NULL != next_node->nodes[LEFT])
	{
		next_node = next_node->nodes[LEFT];
	}
	
	return (next_node);	
}

/******************************************************************************/

bst_iter_t BSTEnd(const bst_t *tree)
{
	bst_t *new_tree = NULL;
	
	assert(tree);
	new_tree = (bst_t *)tree;
	
	return (&new_tree->root_stub);
}

/******************************************************************************/

bst_iter_t BSTFind(bst_t *tree, const void *data)
{
	void *new_data = (void *)data;
	bst_node_t *current_node = NULL;
	bst_node_t *return_node = NULL;
	
	assert(tree);
	return_node = &tree->root_stub;
	current_node = return_node->nodes[direction];;
	
	while (0 != tree->cmp_func(new_data, BSTGetData(current_node), tree->param))
	{
		if (1 == tree->cmp_func(new_data, BSTGetData(current_node), tree->param))
		{
			direction = RIGHT;
		}
		else
		{
			direction = LEFT;
		}
		
		current_node = current_node->nodes[direction];
	}
	
	if (0 == tree->cmp_func(new_data, BSTGetData(current_node), tree->param))
	{
		return_node = current_node;
	}
	
	return (return_node);
}

/******************************************************************************/

bst_iter_t BSTNext(const bst_iter_t iterator)
{
	bst_node_t *next_node = iterator;
	
	assert(iterator);
	
	/* if iterator has bigger value connected - go right */
	/* and than find the minimum value in branch 		 */	
	if (NULL != next_node->nodes[RIGHT])
	{
		next_node = next_node->nodes[RIGHT];
		
		while (NULL != next_node->nodes[LEFT])
		{
			next_node = next_node->nodes[LEFT];
		}
		
		return (next_node);
	}
	/* if iterator is himself a left child - return parent */
	else if (IS_LEFT_CHILD(next_node))
	{
		return (next_node->parent);
	}
	/* if iterator is a right child, and has no left values - move to */
	/* parents until you find parent that is himself a right child    */
	else
	{
		while (NULL != next_node->parent && IS_RIGHT_CHILD(next_node))
		{
			next_node = next_node->parent;
		}
		
		return ((NULL != next_node->parent) ? next_node->parent : next_node);
	}
}

/******************************************************************************/

bst_iter_t BSTPrev(const bst_iter_t iterator)
{
	bst_node_t *current_node = NULL;

	assert(iterator);
	current_node = iterator;
	
	/* if iterator is the stub -> return prev, */  
	/* meaning the biggest value in the tree   */
	if (NULL == current_node->parent) /* add ->data */
	{
		while (NULL != current_node->nodes[RIGHT])
		{
			current_node = current_node->nodes[RIGHT];
		}
		
		return (current_node);
	}
	/* if iterator has left child */
	else if (NULL != current_node->nodes[LEFT])
	{
		current_node = current_node->nodes[LEFT];
		
		while (NULL != current_node->nodes[RIGHT])
		{
			current_node = current_node->nodes[RIGHT];
		}
		
		return (current_node);
	}
	/* if iterator doesn't have left child - 2 options: */
	/* 1: iterator is himself a left child */
	else if (IS_LEFT_CHILD(current_node))
	{
		while (!IS_LEFT_CHILD(current_node->parent))
		{
			current_node = current_node->parent;
		}
		
		return (current_node->parent);
	}
	/* 2: iterator is himself a right child */
	else
	{
		return (current_node->parent);
	}
}

/******************************************************************************/

size_t BSTSize(const bst_t *tree)
{
	bst_node_t *iterator = NULL;
	size_t counter = 0;
	
	assert(tree);
	iterator = BSTBegin(tree);
	
	while (iterator != BSTEnd(tree))
	{
		iterator = BSTNext(iterator);
		++counter;
	}
	
	return (counter);
}

/******************************************************************************/

int BSTIsEmpty(const bst_t *tree)
{
	assert(tree);

	return (NULL == tree->root_stub.nodes[RIGHT] ? 1 : 0);
}
