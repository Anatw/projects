/*******************************************************************************
to compile: gd cpp_before_start_test.c -ldl

                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdio.h> /* printf(), size_t */
#include <dlfcn.h> /* dlopen(), dlsym() */
#include <string.h> /* strcmp() */
#include <stdlib.h> /* atoi() */

char *(*Foo_func)();
char *(*Bla_func)();


int main(int argc, char **argv)
{
    void *sdl_library = NULL;
    char *function = argv[2];
    argc = argc;

    if (strcmp(argv[1], "libbefore.so") == 0)
    {
        sdl_library = dlopen("./libbefore.so", RTLD_LAZY);
        if (NULL == sdl_library)
        {
            printf("ERROR in dlopen.\n");
            return (1);
        }
    }
    else
    {
        printf("Please enter a valid library name.\n");
        return (1);
    }

    /* Get a function called Foo/Bla from this library, and return a pointer to this function so that I can call it: */
    if (strcmp(function, "Foo") == 0)
    {
        *(char **)(&Foo_func) = dlsym(sdl_library, "Foo");
            if (NULL == Foo_func)
        {
            printf("ERROR in dlsym(Foo).\n");
            return (1);
        }
        printf("%s",  Foo_func());
    }
    else if (strcmp(function, "Bla") == 0)
    {
        *(char **)(&Bla_func) = dlsym(sdl_library, "Bla");
        if (NULL == Bla_func)
        {
            printf("ERROR in dlsym(Bla).\n");
            return (1);
        }
        printf("%s", Bla_func());
    }

    dlclose(sdl_library);


    return (0);
}
