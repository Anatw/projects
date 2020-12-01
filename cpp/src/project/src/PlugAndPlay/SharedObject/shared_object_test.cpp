/*******************************************************************************
Plug&Play - Phase 1:
SharedObject class

Written by Anat Wax, anatwax@gmail.com
Created: 27.8.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "shared_object.hpp"
// void InsertionSort(int array[], size_t array_length);
using namespace ilrd;

int main()
{
    void (*func)(void);

    SharedObject shared("/home/anat/git/anat-wax/cpp/src/project/src/"
                        "PlugAndPlay/SharedObject/libtestlib.so");
    *(void**)&func = shared.LoadSymbol< void (*)() >("func");
    func();

    return (0);
}
