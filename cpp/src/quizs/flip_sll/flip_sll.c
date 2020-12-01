/*******************************************************************************
Write a recursive and iterative solutions to fliping a singly linked lised.

Written by Anat Wax, anatwax@gmail.com
Created: 19.8.20
*******************************************************************************/

#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */

typedef struct Node
{
    int data;
    struct Node* next;
} node_t;

node_t* CreateNode(int data)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;

    return (node);
}

void PrintList(node_t* head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("\n");
}

/* recursive flip sll */
node_t* FlipRec(node_t* node)
{
    node_t* new_head = NULL;
    if (NULL == node->next)
    {
        return (node);
    }

    new_head = FlipRec(node->next);
    node->next->next = node;
    node->next = NULL;

    return (new_head);
}

/* iterative flip sll */
node_t* FlipIter(node_t* node)
{
    node_t* prev = NULL;
    node_t* current = node;
    node_t* next = NULL;

    while (NULL != current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return (prev);
}

int main()
{
    node_t* new_head = NULL;
    node_t* head = CreateNode(1);
    head->next = CreateNode(2);
    head->next->next = CreateNode(3);
    head->next->next->next = CreateNode(4);
    head->next->next->next->next = CreateNode(5);

    PrintList(head);
    /*new_head = FlipRec(head);*/
    new_head = FlipIter(head);
    PrintList(new_head);

    return (0);
}
