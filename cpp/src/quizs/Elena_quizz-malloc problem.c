/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <errno.h>  /* error massages */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#define NUMS_IN_INT (4294967296) /* -2,147,483,648 - 2,147,483,647 */
#define CONVERT (2147483648)
#define STRUCTURAL_NODE (533422123)

typedef struct Node
{
    int data;
    struct Node* next;
} node_t;

/*************************/

typedef struct NodeInfo
{
    char occurences;
    node_t* previous_first_node;
} node_info_t;

/*************************/

typedef struct ArrayIndexes
{
    node_info_t array[NUMS_IN_INT];
} array_indexes_t;

/*************************/

typedef struct SLL
{
    node_t* m_array;
    node_t* head;
    node_t* tail;
    node_t* last_node;

} sll_t;

/******************************************************************************/

node_t* CreateNode(sll_t* list, int data)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node)
    {
        printf("ERROR in creating a new node\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;
    list->last_node = new_node;

    return (new_node);
}

sll_t* CreateSLL()
{
    sll_t* list = (sll_t*)malloc(sizeof(sll_t));
    if (!list)
    {
        printf("ERROR in initializating a new list\n");
        exit(EXIT_FAILURE);
    }

    list->head = CreateNode(list, STRUCTURAL_NODE);
    list->head->next = list->tail;

    list->tail = CreateNode(list, STRUCTURAL_NODE);
    list->tail->next = NULL;

    list->last_node = list->head;

    return (list);
}

void Insert(sll_t* list, int data)
{
    node_t* node = CreateNode(list, data);
    node->next = list->tail;
    list->last_node = node;
}

void DeleteNextNode(node_t* to_delete)
{
    to_delete->next = to_delete->next->next;
}

array_indexes_t* IniailizeDupArray()
{
    array_indexes_t* array_info =
        (array_indexes_t*)malloc(sizeof(array_indexes_t));

    if (!array_info)
    {
        printf("ERROR in initializating a new list's array\n");
        exit(EXIT_FAILURE);
    }

    return (array_info);
}

void ClearDuplicates(node_t* head)
{
    node_t* temp_node = NULL;
    node_t* next_node = head->next;
    int current_data = 0;

    array_indexes_t* array_info = IniailizeDupArray();

    ++(array_info->array[head->data].occurences);

    while (NULL != head)
    {
        if (next_node->data > 0)
        {
            current_data = next_node->data + CONVERT;

            if (0 == (array_info->array[current_data]
                          .occurences)) /* First occurence of the data */
            {
                ++array_info->array[current_data].occurences;
                array_info->array[current_data].previous_first_node = head;
            }
            else /* second or more occurences of the data */
            {
                if (NULL != array_info->array[current_data].previous_first_node)
                {
                    DeleteNextNode(
                        array_info->array[current_data].previous_first_node);
                    array_info->array[current_data].previous_first_node = NULL;
                }

                temp_node = head;
                head = head->next;
                DeleteNextNode(temp_node);
            }
        }
        else
        {
            current_data = current_data;

            if (0 == (array_info->array[current_data]
                          .occurences)) /* First occurence of the data */
            {
                ++array_info->array[current_data].occurences;
                array_info->array[current_data].previous_first_node = head;
            }
            else /* second or more occurences of the data */
            {
                if (NULL != array_info->array[current_data].previous_first_node)
                {
                    DeleteNextNode(
                        array_info->array[current_data].previous_first_node);
                    array_info->array[current_data].previous_first_node = NULL;
                }

                temp_node = head;
                head = head->next;
                DeleteNextNode(temp_node);
            }
        }
    }
}

int main()
{
    sll_t* list = CreateSLL();
    Insert(list, 1);
    Insert(list, 2);
    Insert(list, 4);
    Insert(list, 7);
    Insert(list, 2);
    Insert(list, 11);
    Insert(list, 2);

    /* ClearDuplicates(list->head); */

    return (0);
}
