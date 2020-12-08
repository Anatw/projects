#include <iostream>  /* cout, cin, cerr */
#include <exception> /* std:set_terminate */
#include <cstdlib>   // std::abort

using namespace std;

class X
{
public:
    ~X();
    int Foo(int x);

private:
    int m_a;
};

void Bar()
{
    throw(-1);
}

X::~X()
{
    cerr << X::Foo(m_a) << endl;
}

void Fishi()
{
    X x1;

    Bar();
}

void term_func()
{
    cout << "term_func has been caled by terminate()" << endl;
    abort();
}
int X::Foo(int x)
{
    throw(0);
}

int main()
{
    Fishi();

    try
    {
        Bar();
    }

    catch (int)
    {
        cout << "Cought an integer error...\n";
    }

    return (0);
}
