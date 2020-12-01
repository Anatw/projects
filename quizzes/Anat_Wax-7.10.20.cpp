/*******************************************************************************
Implement Quack using 3 stacks:
A quack is a data structure combining properties of both stacks (LIFO) and
queues (FIFO). It can be viewed as a list of elements written left to right such
that three operations are possible:
 • push(x): add a new item x to the left end of the list. (list: x____z)
 • pop(): remove and return the item on the left end of the list. (return x;
   list: ____z)
 • pull(): remove the item on the right end of the list. (return z; list: ____)
Implement a quack using three stacks and O(1) additional memory, so that the
amortized time for any push, pop, or pull operation is O(1).

Written by Anat Wax, anatwax@gmail.com
Created: 7.10.20
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <stack>

namespace ilrd
{

class Quack
{
public:
    Quack();

    void push(int v);
    int pop();
    int pull();

private:
    int m_size;

    std::stack< int > s1;
    std::stack< int > s2;
    std::stack< int > s3;
};

Quack::Quack() : m_size(0)
{
}

void Quack::push(int v)
{
}

int Quack::pop()
{
}

int Quack::pull()
{
}

} // namespace ilrd

using namespace ilrd;

int main()
{
    Quack quack;

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions: //
////////////////////////////////////////////////////////////////////////////////
