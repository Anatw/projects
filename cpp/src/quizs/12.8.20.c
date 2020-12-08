/*******************************************************************************
Given a full tree with values only in leafs, sum all the tree.
Struct Node
{
   int val;
   Node* left;
   Node* right;
}

answer should be a function SumTree.

Written by Anat Wax, anatwax@gmail.com
Created: 12.8.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

typedef struct Node
{
    int val;
    struct Node* left;
    struct Node* right;
} node_t;

void SumTree(node_t* current, size_t* leaf_sum) /* current = root at first run*/
{
    if (!current)
    {
        return;
    }

    if (current->left == NULL && NULL == current->right)
    {
        *leaf_sum += current->val;
        return;
    }

    SumTree(current->left, leaf_sum);
    SumTree(current->right, leaf_sum);
}

node_t* CreateNode(int val)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->val = val;
    node->right = NULL;
    node->left = NULL;

    return (node);
}

int main()
{
    size_t sum = 0;
    node_t* root = CreateNode(5);
    root->left = CreateNode(4);
    root->left->left = CreateNode(2); /* leaf */
    root->right = CreateNode(5);
    root->right->left = CreateNode(1);  /* leaf */
    root->right->right = CreateNode(3); /* leaf */

    /*printf("%ld\n", SumTree(root, &sum));*/
    SumTree(root, &sum);
    printf("%ld\n", sum);

    return (0);
}

/* needed fix:
1. function should return void and not size_t;
2. another condition should be added - if (!current)
*/
