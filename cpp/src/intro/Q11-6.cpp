#include <iostream> /* cout, cin, cerr */
#include <dlfcn.h> /* dlopen(), dlsym(), dlclose() */

#include "Q11.h"

int main()
{
    void *handle = dlopen("./libquestion11.so", RTLD_LAZY);
    char i='a';
    int t = 9;
    float f = 4.7;
    int *p_int = &t;
    char *p_char = NULL;
    unsigned char u = 't';
    typedef void (*hello_t)();

    // reset errors
    dlerror();
    hello_t hello = (hello_t) dlsym(handle, "Foo");
    const char *dlsym_error = dlerror();
    
    Foo(i);
    Foo(t);
    Foo(f);
    Foo(p_int);
    Foo(*p_int);
    
    Foo(u);

    
    Foo(*p_char);
    Foo(p_char);
    //std::cout << ;

    return (0);
}