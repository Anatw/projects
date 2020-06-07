#include <iostream>
#include <exception> // bad_alloc
#include <string>
#include <cstdlib>

using namespace std;

class Printer
{
public:
    Printer()
    {
        cout << "Printers' Ctor" << endl;
    }
    ~Printer()
    {
        cout << "Printers' Dtor!" << endl;
    }
};

struct BadDog : public runtime_error
{
    BadDog(const string &s_ = "This is a bad dog") : runtime_error(s_) {}
};

void Fifi()
{
    //throw("bad pupy!!");
    throw BadDog("bad pup");
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    Printer *x = new Printer;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
    delete x;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    try
    {
        Bar();
    }
    catch (bad_alloc &)
    {
        cerr << "Out of memory! exiting.";
        exit(2);
    }
    catch (BadDog b)
    {
        cerr << "Bad dog exception: " << b.what();
        exit(3);
    }
    catch (exception &r)
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }
    catch (...)
    {
        cout << "general exception: " << endl;
        exit(5);
    }

    return (0);
}
