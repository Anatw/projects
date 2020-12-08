/*******************************************************************************
Plug&Play - Phase 1:
SharedObject class

Written by Anat Wax, anatwax@gmail.com
Created: 27.8.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr
extern "C"
{
    void func();

    void func()
    {
        std::cout << "I am a pretty func" << std::endl;
    }
}
