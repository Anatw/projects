/*******************************************************************************
The four functions dlopen(), dlsym(), dlclose(), dlerror() implement the interface to the dynamic linking loader.

                        C++ before you start
                        Written by Anat Wax
                          May 23rd, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */


char *Foo()
{
    return("Hello! I am Foo()\n");
}

char *Bla()
{
    return("Bla bla bla\n");
}