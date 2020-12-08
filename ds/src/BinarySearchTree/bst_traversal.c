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

#include "../../include/binary_search_tree.h"
#include "../../include/stack.h"

/*void PreOrder(bst_iter_t root)
{
    bst_iter_t current = root;

    while (current->parent != NULL)
    {
        if (current->left != NULL)
        {
            while (NULL != current->left)
            {
                current = current->left;
            }
            printf("%d\n", current->data);
        }
        else
        {
            if (current->right != NULL)
            {
                current = current->right;
            }
            else
            {
                current = current->parent;
            }
        }
    }
}*/

int CmpFunc(const void* data1, const void* data2, const void* param)
{
    return ((*(int*)data1 > *(int*)data2) ? *(int*)data2 : *(int*)data1);
}

int main()
{
    bst_t* tree = BSTCreate(CmpFunc, NULL);
    int data1 = 4;
    int data2 = 6;
    int data3 = 3;
    int data4 = 7;
    int data5 = 9;

    BSTInsert(tree, &data1);
    BSTInsert(tree, &data2);
    BSTInsert(tree, &data3);
    BSTInsert(tree, &data4);
    BSTInsert(tree, &data5);

    return (0);
}
