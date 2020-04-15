/*******************************************************************************
 * File: binary_search_tree.c - operation funcs					 		   	   *
 * Author: Ya'acov Evenchik                                                    *
 * Reviewed by: Anat				                                		   *
 * Date: 		    05.04.2020                                             	   *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "binary_search_tree.h"

typedef enum
{
	LEFT,
	RIGHT,
	NUM_SONS
} children_e;

typedef struct bst_node
{
	struct bst_node *parent;
	struct bst_node *nodes[NUM_SONS];
	void *data;
} bst_node_t;

struct binary_search_tree
{
	bst_node_t root_stub;
	int (*cmp_func)(const void *data1, const void *data2, const void *param);
	void *param;
};

static children_e LeftOrRightParent(bst_iter_t iterator);


/*****************************************************************************/

bst_t *BSTCreate(int (*cmp_func)(const void *data1, const void *data2,
                                 const void *param),
                 const void *param)
{
	bst_t *tree = NULL;

	assert(cmp_func);
	assert(param);

	tree = (bst_t *)malloc(sizeof(bst_t));

	if(NULL == tree)
	{
		return (NULL);
	}
	
	tree->root_stub.parent = NULL;
	tree->root_stub.nodes[RIGHT] = NULL;
	tree->root_stub.nodes[LEFT] = &(tree->root_stub);
	tree->root_stub.data = NULL;
	tree->cmp_func = cmp_func;
	tree->param = &param;

	return (tree);
}

/*****************************************************************************/

void BSTDestroy(bst_t *tree)
{
	bst_iter_t remove = NULL;
	bst_iter_t check = NULL;

	assert(tree);

	check = BSTBegin(tree);
	remove = check;

	while (0 == BSTIsEmpty(tree))
	{
		/* check if leaf */
		if (NULL == check->nodes[RIGHT] && NULL == check->nodes[LEFT])
		{
			check = check->parent;
			BSTRemove(remove);
		}
		/* if largest value */
		else if (NULL != check->nodes[RIGHT] && NULL == check->nodes[RIGHT]->data)
		{
			check = check->parent;
			BSTRemove(remove);
		}
		/* if not leaf continue to next */
		else
		{
			check = BSTNext(check);
		}
		
		remove = check;
	}

	free(tree);
	tree = NULL;	
}

/*****************************************************************************/

bst_iter_t BSTBegin(const bst_t *tree)
{	 
	bst_iter_t begin = NULL;
	
	assert(tree);

	begin = (bst_iter_t)&(tree->root_stub);

	if (BSTIsEmpty(tree))
	{
		return (begin);
	}
	
	while (NULL != begin->nodes[LEFT])
	{
		begin = begin->nodes[LEFT];
	}

	return (begin);
}

/*****************************************************************************/

bst_iter_t BSTEnd(const bst_t *tree)
{	
	assert(tree);
	
	return ((bst_iter_t )&(tree->root_stub));
}

/*****************************************************************************/

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_iter_t current_node = NULL;
	bst_iter_t former_node = NULL;
	bst_iter_t insert = NULL;
	children_e direction = LEFT;

	assert(tree);
	assert(data);
		
	insert = (bst_node_t *)malloc(sizeof(bst_node_t));

	if (NULL == insert)
	{
		return (NULL);
	}

	current_node = tree->root_stub.nodes[LEFT];
	former_node = &(tree->root_stub);

	/* looping tree until correct location found */
	while (NULL != current_node && !BSTIsEqual(BSTEnd(tree), current_node))
	{
		former_node = current_node;

		if (LEFT == (tree->cmp_func)(data, BSTGetData(current_node), tree->param))
		{
			direction = LEFT;
			current_node = current_node->nodes[direction];
		}
		else if (RIGHT == (tree->cmp_func)(data, BSTGetData(current_node),
							 tree->param))
		{
			direction = RIGHT;
			current_node = current_node->nodes[direction];
		}
	}

	/* if inserted node contains largest value */ 
	if (BSTIsEqual(BSTEnd(tree), current_node))
	{
		insert->nodes[RIGHT] = BSTEnd(tree);
		tree->root_stub.parent = insert;
	}
	else
	{
		insert->nodes[RIGHT] = NULL;
	}

	former_node->nodes[direction] = insert;
	insert->parent = former_node;
	insert->nodes[LEFT] = NULL;	
	insert->data = (void *)data;

	return (insert);
}

/*****************************************************************************/

void BSTRemove(bst_iter_t iterator)
{
	bst_iter_t swap = iterator;
	children_e parent_direction = LEFT;

	assert(iterator);

	/* compare to parent */
	parent_direction = LeftOrRightParent(iterator);

	/* check if childless */
	if (NULL == iterator->nodes[RIGHT] && NULL == iterator->nodes[LEFT])
	{
		iterator->parent->nodes[parent_direction] = NULL;
	}
	/* 2 children */
	else if (NULL != iterator->nodes[RIGHT] && NULL != iterator->nodes[LEFT])
	{
		swap = iterator->nodes[LEFT];

		while (NULL != swap->nodes[RIGHT])
		{
			swap = swap->nodes[RIGHT];
		}

		/* if last LEFT on branch dosnt have a RIGHT */
		if (NULL == swap->nodes[LEFT])
		{	
			if(iterator->nodes[LEFT] == swap)
			{
				swap->parent->nodes[RIGHT] = iterator->nodes[RIGHT];
				swap->nodes[LEFT] = NULL;
				swap->parent = iterator->parent;
			}
			else
			{
				swap->parent->nodes[RIGHT] = NULL;
				swap->nodes[LEFT] = iterator->nodes[LEFT];
				iterator->nodes[LEFT]->parent = swap;
				swap->parent = iterator->parent;
			}

			swap->nodes[RIGHT] = iterator->nodes[RIGHT];
			iterator->nodes[RIGHT]->parent = swap;
			iterator->parent->nodes[parent_direction] = swap;
		}
		else
		{
			if (iterator->nodes[LEFT] != swap)
			{
				swap->parent->nodes[RIGHT] = swap->nodes[LEFT];
				swap->nodes[LEFT]->parent = swap->parent;
				swap->nodes[LEFT] = iterator->nodes[LEFT];
				iterator->nodes[LEFT]->parent = swap;
			}

			swap->nodes[RIGHT] = iterator->nodes[RIGHT];
			iterator->nodes[RIGHT]->parent = swap;
			swap->parent = iterator->parent;
			iterator->parent->nodes[parent_direction] = swap;
		}		
	}
	/* if there is 1 child */
	else if (NULL != iterator->nodes[LEFT])
	{
		iterator->nodes[LEFT]->parent = iterator->parent;
		iterator->parent->nodes[parent_direction] = iterator->nodes[LEFT];
	}
	else
	{
		iterator->nodes[RIGHT]->parent = iterator->parent;
		iterator->parent->nodes[parent_direction] = iterator->nodes[RIGHT];
	}
	
	free(iterator);
	iterator = NULL;
}

/*****************************************************************************/

bst_iter_t BSTFind(bst_t *tree, const void *data)
{
	bst_iter_t to_find = NULL;
	children_e direction = LEFT;

	assert(tree && data);

	to_find = tree->root_stub.nodes[LEFT];

	while (NULL != to_find && !BSTIsEqual(BSTEnd(tree), to_find))
	{		
		if (LEFT == (tree->cmp_func)(data, BSTGetData(to_find), tree->param))
		{
			direction = LEFT;
			to_find = to_find->nodes[direction];
		}
		else if (RIGHT == (tree->cmp_func)(data, BSTGetData(to_find), tree->param))
		{
			direction = RIGHT;
			to_find = to_find->nodes[direction];
		}
		/* The data in the element is equal to the searched data */
		else
		{
			return (to_find);
		}
	}
	
	/* Couldn't find a match */
	return (NULL);
}

/*****************************************************************************/

int BSTIsEmpty(const bst_t *tree)
{
	assert(tree);

	return (&(tree->root_stub) == tree->root_stub.nodes[LEFT]);
}

/*****************************************************************************/

int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{
	return (iter1 == iter2);
}

/*****************************************************************************/

void *BSTGetData(const bst_iter_t iterator)
{
	assert(iterator);

	return (iterator->data);
}

/*****************************************************************************/

bst_iter_t BSTNext(const bst_iter_t iterator) 
{
	bst_iter_t next = NULL;
	
	assert(iterator);
	
	next = iterator->parent;
	
	/* If there is a RIGHT child */
	if (NULL != iterator->nodes[RIGHT])
	{
		next = iterator->nodes[RIGHT];
		
		/* In case of highest value return the bst */
		if (next->data == NULL)
		{
			return (next);
		}
		
		/* While there are LEFT children in the branch */
		while (next->nodes[LEFT])
		{
			next = next->nodes[LEFT];
		}

		return (next);
	}
	
	/* If there is a LEFT parent, go on them until a RIGHT parent */
	else if (next->nodes[RIGHT] == iterator)
	{
		while (next->parent->nodes[RIGHT] == next)
		{
			next = next->parent;
		}
		
		return (next->parent);
	}

	return (next);
}

/*****************************************************************************/

bst_iter_t BSTPrev(const bst_iter_t iterator)  /**** need fixing *****/
{
	bst_iter_t prev = NULL;
	
	assert(iterator);
	
	prev = iterator->parent;
	
	/* If iterator is the bst */
	if (NULL == iterator->data)
	{
		return (prev);
	}
	
	/* If there is a LEFT child */
	if (NULL != iterator->nodes[LEFT])
	{
		prev = iterator->nodes[LEFT];
		
		/* While there are RIGHT children in the branch */
		while (prev->nodes[RIGHT])
		{
			prev = prev->nodes[RIGHT];
		}

		return (prev);
	}
	
	/* If RIGHT parent, go up until a LEFT parent */
	else if(prev->nodes[LEFT] == iterator)
	{
		while (prev->parent->nodes[LEFT] == prev)
		{
			prev = prev->parent;
		}
		
		return (prev->parent);
	}

	return (prev);
}

/*****************************************************************************/

size_t BSTSize(const bst_t *tree)
{
	bst_iter_t check = NULL;
	size_t count = 0;

	assert(tree);
	
	if (1 == BSTIsEmpty(tree))
	{
		return (0);
	}
	
	check = BSTBegin(tree);
	
	for (check = BSTBegin(tree); !BSTIsEqual(check, BSTEnd(tree));
		 check = BSTNext(check))
	{
		++count;
	}
	
	return (count);	
}

/*****************************************************************************/

int BSTForEach(const bst_iter_t from,
               const bst_iter_t to,
               int (*opr_func)(const void *data, const void *param),
               const void *param)
{
	bst_iter_t iterator = NULL;
	int status = 1;

	assert(opr_func);
	assert(param);

	for (iterator = from;
		!BSTIsEqual(iterator, to); 
		 iterator = BSTNext(iterator))
	{
		status = opr_func(iterator->data, param);
		
		if (1 != status)
		{
			break;
		}
	}

	return (status);
}

/*****************************************************************************/
/**********************    assistant funcs    ************************/

static children_e LeftOrRightParent(bst_iter_t iterator)
{
	children_e parent_direction = RIGHT;

	assert(iterator);

	/* compare to parent */
	if (NULL != iterator->parent)
	{
		if (BSTIsEqual(iterator, iterator->parent->nodes[RIGHT]))
		{
			parent_direction = RIGHT;
		}
		else
		{
			parent_direction = LEFT;
		}
	}

	return (parent_direction);
}

int PrintTreePostOrder(bst_t *tree)
{
	bst_iter_t to_remove = NULL;
	bst_iter_t check = NULL;
	int root = 0;
	
	assert(tree);
	
	check = BSTBegin(tree);
	to_remove = check;
	
	/* Iterating Post-Order from BSTBegin */
	while (0 == BSTIsEmpty(tree))
	{
		/* If it's a leaf, remove it */
		if (NULL == check->nodes[LEFT] && NULL == check->nodes[RIGHT])
		{
			check = check->parent;
			printf("%d ,", *((int *)BSTGetData(to_remove)));
			BSTRemove(to_remove);	
		}
		
		/* If it is the element with highet value */
		else if (check->nodes[RIGHT] != NULL && check->nodes[RIGHT]->data == NULL)
		{
			check = check->parent;
			root = *((int *)BSTGetData(to_remove));
			printf("%d ,", *((int *)BSTGetData(to_remove)));
			BSTRemove(to_remove);
		}
		
		/* Not a leaf, go down the branch till getting to a leaf */
		else
		{
			check = BSTNext(check);
		}
		to_remove = check;
	}
	
	/* Removing the bst struct and freeing the tree */
	free(tree);
	tree = NULL;
	printf("\n\n");
	
	return (root);
}


