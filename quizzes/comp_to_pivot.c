/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
Created: 17.8.20
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

/* Link list Node */
typedef struct Node
{
    int data;
    struct Node* next;
} node_t;

node_t* CreateNode(int data)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;

    return (new_node);
}

/******************************************************************************/

node_t* CompToPivot(node_t* node, int pivot)
{
    node_t *smaller_head = NULL, *smaller_end = NULL;
    node_t *greater_end = NULL, *greater_head = NULL;
    node_t *equal_head = NULL, *equal_end = NULL;

    while (node != NULL)
    {
        if (node->data == pivot)
        {
            if (equal_head == NULL)
                equal_head = equal_end = node;
            else
            {
                equal_end->next = node;
                equal_end = equal_end->next;
            }
        }

        else if (node->data < pivot)
        {
            if (smaller_head == NULL)
                smaller_end = smaller_head = node;
            else
            {
                smaller_end->next = node;
                smaller_end = node;
            }
        }
        else
        {
            if (greater_head == NULL)
                greater_end = greater_head = node;
            else
            {
                greater_end->next = node;
                greater_end = node;
            }
        }

        node = node->next;
    }

    if (greater_end != NULL)
    {
        greater_end->next = NULL;
    }

    if (smaller_head == NULL)
    {
        if (equal_head == NULL)
            return greater_head;
        equal_end->next = greater_head;
        return equal_head;
    }

    if (equal_head == NULL)
    {
        smaller_end->next = greater_head;
        return smaller_head;
    }

    smaller_end->next = equal_head;
    equal_end->next = greater_head;

    return smaller_head;
}

void PrintList(node_t* node)
{
    node_t* temp = node;

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main()
{
    node_t* head = CreateNode(1);
    int pivot = 7;

    head->next = CreateNode(9);
    head->next->next = CreateNode(5);
    head->next->next->next = CreateNode(9);
    head->next->next->next->next = CreateNode(9);
    head->next->next->next->next->next = CreateNode(4);
    head->next->next->next->next->next->next = CreateNode(6);

    printf("before\n");
    PrintList(head);

    head = CompToPivot(head, pivot);

    printf("after\n");
    PrintList(head);

    return (0);
}
