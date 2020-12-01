#include <iostream> /* cout, cin, cerr */
// -fno-use-cxa-atexit  :add this to the compilation when creating the 0 file - this is because i don't need destruction of static object.

#include "Q11.h"



void Foo()
{

}
void Foo(int i)
{
    std::cout << i << "\n";
}
void Foo(char c)
{
    std::cout << c << "\n";
}
void Foo(float i)
{
    std::cout << i << "\n";
}
void Foo(int *c)
{
    std::cout << c << "\n";
}
void Foo(char *i)
{
    std::cout << i << "\n";
}
void Foo(unsigned char c)
{
    std::cout << c << "\n";
}
