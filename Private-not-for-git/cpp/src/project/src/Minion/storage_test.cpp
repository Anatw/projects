/*******************************************************************************
Storage class (part of project Minion) - test
Written by Anat Wax, anatwax@gmail.com
Created: 4.8.20
Reviewer: Shumuel Sinder
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "storage.hpp"

using namespace std;
using namespace ilrd;

#define BLOCK_SIZE (100)

int main()
{
    Storage< BLOCK_SIZE > storage(BLOCK_SIZE);
    string first("hello");
    string second("world");
    storage.Write(10, first.c_str());
    storage.Write(12, second.c_str());

    char dest[BLOCK_SIZE];

    storage.Read(12, dest);
    cout << dest << endl;
    storage.Read(10, dest);
    cout << dest << endl;

    return (0);
}
