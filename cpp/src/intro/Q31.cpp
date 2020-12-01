#include <iostream>  /* cout, cin, cerr */
#include <exception> /* std:set_terminate */
#include <cstdlib>   // std::abort

using namespace std;

void term_func()
{
    cout << "term_func has been caled by terminate()" << endl;
    abort();
}
int foo()
{
    throw(1);
}

int main()
{
    set_terminate(term_func);

    cout << "Just entered main!" << endl;
    try
    {
        foo();
    }

    catch (float)
    {
        cout << "Cought an integer error...\n";
        term_func();
    }
    /* interesting!:
    in catch, when argument is an int, the terminal print is:
    Just entered main!
    Cought an integer error...

    when argument is an float, the terminal print is:
    Just entered main!
    term_func has been caled by terminate()
    Makefile:24: recipe for target 'test' failed
    make: *** [test] Aborted (core dumped)
    The terminal process terminated with exit code: 2

    With no exception handlers:
    Just entered main!
    terminate called after throwing an instance of 'int'
    Makefile:24: recipe for target 'test' failed
    make: *** [test] Aborted (core dumped)
    The terminal process terminated with exit code: 2
    */

    return (0);
}
