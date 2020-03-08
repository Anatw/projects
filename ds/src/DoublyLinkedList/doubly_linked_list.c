#include <stdio.h>
#include <stdlib.h> /* malloc() */

#include "doubly_linked_list.h"

/* type of node in the list */
typedef struct dll_node
{
	void *data; /* pointer to the data the node contain */
	struct dll_node *next; /* pointer to the next node */
	struct dll_node *prev; /* pointer to the previous node */
} dll_node_t;

struct doubly_linked_list
{
	dll_node_t head;
	dll_node_t tail;
}/* dll_t */;


static dll_node_t *DLL_CreateNode(void *data)
{
	dll_node_t *new_node = NULL;
	
	new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	new_node->data = data;
	new_node->next = NULL;
	
	return (new_node);
}


dll_t *DLLCreate()
{
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	list->head.next = &list->tail;
	list->tail.prev = &list->head;
	list->tail.next = NULL;
	
	return (list);
}

void DLLDestroy(dll_t *list)
{
	free(list);
}

iter_t DLLBegin(dll_t *list)
{
	return (list->head.next);
}

iter_t DLLEnd(dll_t *list)
{
	return (list->tail.prev);
}















