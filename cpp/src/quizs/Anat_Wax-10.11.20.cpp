/*******************************************************************************
A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.
Given the root to a binary tree, count the number of unival subtrees.
For example, the following tree has 5 unival subtrees:
  a
 / \
a   a
    /\
   a  a
       \
        A
This tree has 3 unival subtrees: the two 'a' leaves, and the one 'A' leaf. The 'A' leaf causes all its parents to not be counted as a unival tree.

  a
 / \
c   b
    /\
   b  b
        \
         b
This tree has 5 unival subtrees: the leaf at 'c', and every 'b'.


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 10.11.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <stack>

class node_t
{
public:
    node_t() : left(NULL), right(NULL) {}
    inline bool IsChildless() const
    {
        return ((left == NULL && right == NULL) ? true : false);
    }
    inline int GetData()
    {
        return data;
    }

    inline node_t *LeftChild()
    {
        return (this->left);
    }

    inline node_t *RightChild()
    {
        return (this->left);
    }
private:
    int data;
    struct node_t *left;
    struct node_t *right;
};

int CountUnivalTrees(node_t *root)
{
    std::stack<node_t *> stack;
    node_t *iterator = root;
    int counter;

    stack.push(iterator);
    while (!stack.empty())
    {
        iterator = iterator->LeftChild();
        while (stack.top()->GetData() == iterator->GetData())
        {
            if (iterator->IsChildless())
            {
                ++counter;
                iterator = stack.top(); // peek the top element in the queue
            }
            iterator = iterator->RightChild();
            stack.push(iterator);
        }

    }
}

int main()
{
    
    return 0;
}