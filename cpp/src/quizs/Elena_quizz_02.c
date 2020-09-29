/*******************************************************************************
A program that creates a singly linked list and has a function,
ClearDuplicates(), that clear ALL occurences of the node containing the data if
the data appers more than once in the list.

Written by Anat Wax,
anatwax@gmail.com Created: 26.9.20
*******************************************************************************/
#include <errno.h>  /* error massages */
#include <stdint.h> /* uint8_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

/*#define DNDBUG*/

#define POS_INT (2147483647) /* -2,147,483,648 - 2,147,483,647 */
#define NEG_INT (2147483648) /* -2,147,483,648 - 2,147,483,647 */
#define CONVERT (2147483648)
#define STRUCTURAL_NODE (533422123)
#define CHAR (255)

typedef struct Node
{
    int data;
    struct Node* next;
} node_t;

typedef struct SLL
{
    node_t* m_array;
    node_t* head;
    node_t* last_node;
    uint8_t* pos_occur_counter;
    uint8_t* neg_occur_counter;
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

    if (0 <= data) /* positive data */
    {
        ++list->pos_occur_counter[data];
    }
    else
    {
        data *= (-1);
        ++list->neg_occur_counter[data];
    }

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

    list->pos_occur_counter = (uint8_t*)calloc(POS_INT, sizeof(uint8_t));
    if (!list->pos_occur_counter)
    {
        printf("ERROR in allocating list->pos_occur_counter\n");
        exit(EXIT_FAILURE);
    }

    list->neg_occur_counter = (uint8_t*)calloc(NEG_INT, sizeof(uint8_t));
    if (!list->neg_occur_counter)
    {
        printf("ERROR in allocating list->neg_occur_counter\n");
        free(list->pos_occur_counter);
        list->pos_occur_counter = NULL;
        exit(EXIT_FAILURE);
    }

    list->head = CreateNode(list, STRUCTURAL_NODE);
    list->last_node = list->head;

    return (list);
}

void Insert(sll_t* list, int data)
{
    node_t* node = CreateNode(list, data);
    list->last_node->next = node;
    list->last_node = node;
}

node_t* SLLRemove(node_t* who)
{
    node_t* temp = who->next;

    who->data = who->next->data;
    who->next = who->next->next;

    free(temp);
    temp = NULL;

    return (who);
}

void ClearDuplicates(sll_t* list)
{
    node_t* current_node = list->head->next;

    while (NULL != current_node->next)
    {
        if (current_node->data >= 0) /* Positive data */
        {
            if (1 < (list->pos_occur_counter[current_node->data]))
            {
                SLLRemove(current_node);
            }
        }
        else
        {
            if (1 < (list->neg_occur_counter[-(current_node->data)]))
            {
                SLLRemove(current_node);
            }
        }

        if (current_node->next != NULL)
        {
            /* The current_node can only change if you are not in a middle of a
             * multy-erasing situation  - only if the next node's data doesn't
             * appear multiple time in the list than the curren_node can change
             */
            if (((current_node->data >= 0) &&
                 1 >= (list->pos_occur_counter[current_node->data])) ||
                ((current_node->data < 0) &&
                 1 >= (list->neg_occur_counter[-(current_node->data)])))
            {
                current_node = current_node->next;
            }
        }
    }
}

void PrintList(sll_t* list)
{
#ifdef DNDBUG
    int counter = 0;
#endif /* DNDBUG */
    node_t* node = list->head->next;
    while (NULL != node->next)
    {
        printf("%d->", node->data);
        node = node->next;
#ifdef DNDBUG
        ++counter;
#endif /* DNDBUG */
    }
    printf("%d->", node->data);
    printf("NULL\n");
#ifdef DNDBUG
    printf("counter = %d\n", counter);
#endif /* DNDBUG */
}

void DeleteList(sll_t* list)
{
#ifdef DNDBUG
    int counter = 0;
#endif /* DNDBUG */
    node_t* node = list->head;
    node_t* next_node = node->next;

    while (NULL != node->next)
    {
        free(node);
        node = NULL;
#ifdef DNDBUG
        ++counter;
#endif /* DNDBUG */

        node = next_node;
        next_node = next_node->next;
    }

    free(node);
    node = NULL;
    free(list->pos_occur_counter);
    list->pos_occur_counter = NULL;
    free(list->neg_occur_counter);
    list->neg_occur_counter = NULL;

    free(list);
    list = NULL;

#ifdef DNDBUG
    printf("DeleteList counter = %d\n", counter);
#endif /* DNDBUG */
}

int main()
{
    sll_t* list = CreateSLL();
    int i = 355;
    Insert(list, 1);
    Insert(list, 2133);
    while (i > 0)
    {
        Insert(list, 21);
        --i;
    }
    Insert(list, 2133);
    Insert(list, 2133);
    Insert(list, 2133);
    Insert(list, 2133);
    Insert(list, 1);
    Insert(list, 4);
    Insert(list, 7);
    Insert(list, 21);
    Insert(list, 11);
    Insert(list, 21);
    Insert(list, -22);
    Insert(list, 0);
    Insert(list, 0);
    Insert(list, 8862);
    Insert(list, 8356722);
    Insert(list, 22);
    Insert(list, 21);
    Insert(list, -22);
    Insert(list, -2);
    Insert(list, 0);
    Insert(list, 0);
    Insert(list, 0);
    Insert(list, 0);
    Insert(list, 0);
    Insert(list, 5);

    printf("Before:\n");
    PrintList(list);

    ClearDuplicates(list);

    printf("\nAfter:\n");
    PrintList(list);

    DeleteList(list);

    return (0);
}
