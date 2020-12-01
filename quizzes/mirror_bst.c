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

void MirrorBst(node_t* root)
{
    node_t* temp_node = NULL;

    if (root == NULL)
    {
        return;
    }

    temp_node = root->left;
    root->left = root->right;
    root->right = temp_node;

    MirrorBst(root->left);
    MirrorBst(root->right);
}

int main()
{

    return (0);
}
