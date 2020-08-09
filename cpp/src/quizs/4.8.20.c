/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

typedef struct node
{
    struct node* right;
    struct node* left;
    int data;
} node_t;

node_t* CreateNode(int val)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = val;

    return (new_node);
}

size_t Max(int first, int second)
{
    return (first > second ? first : second);
}

size_t MaxSum(node_t* current)
{
    if (NULL == current)
    {

        return (0);
    }

    return (Max(MaxSum(current->left), MaxSum(current->right)) + current->data);
}

size_t MaxSumS(node_t* current)
{
    static size_t sum = 0;

    if (NULL == current)
    {

        return (0);
    }

    return (sum +=
            Max(MaxSum(current->left), MaxSum(current->right)) + current->data);
}

int main()
{
    /* building the tree */
    node_t* root = CreateNode(2);
    root->left = CreateNode(7);
    root->right = CreateNode(5);
    root->left->left = CreateNode(4);
    root->left->right = CreateNode(9);
    root->right->left = root->left->right;
    root->right->right = CreateNode(4);

    printf("maximal sum: %ld\n", MaxSum(root));
    printf("maximal sum: %ld\n", MaxSumS(root));

    return 0;
}
