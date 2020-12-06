#include <iostream>
#include <typeinfo> // bad_cast()

using namespace std;

struct X
{
    X()
    {
        cerr << "X Ctor" << endl;
        throw bad_cast();
    }
    X(int) { cerr << "X Ctor (int)" << endl; }
    ~X() { cerr << "X Dtor" << endl; }
};

struct Y
{
    Y() { cerr << "Y Ctor" << endl; }
    ~Y() { cerr << "Y Dtor" << endl; }
};

class L
{
public:
    L() : m_x(2) { cerr << "L Ctor" << endl; }
    ~L() { cerr << "L Dtor" << endl; }

private:
    Y m_y;
    X m_x;
};

class M
{
public:
    M() { cerr << "M Ctor" << endl; }
    ~M() { cerr << "M Dtor" << endl; }

private:
    X m_x;
    Y m_y;
};

// Best one after L...:
class N
{
public:
    N() { cerr << "N Ctor" << endl; }
    ~N() { cerr << "N Dtor" << endl; }

private:
    Y m_y;
    X m_x;
};

class J
{
public:
    J() : m_y(new Y), m_x(new X) { cerr << "J Ctor" << endl; }
    ~J()
    {
        cerr << "J Dtor" << endl;
        delete m_x;
        delete m_y;
    }

private:
    Y *m_y;
    X *m_x;
};

class K
{
public:
    K()
    {
        cerr << "K Ctor" << endl;
        m_y = new Y;
        m_x = new X;
    }
    ~K()
    {
        cerr << "K Dtor" << endl;
        delete m_x;
        delete m_y;
    }

private:
    Y *m_y;
    X *m_x;
};

int main()
{

    try
    {
        K var1;
    }
    catch (exception &e)
    {
        cerr << "exception cout. what:" << e.what() << endl;
    }

    return (0);
}

/*
L:
Y Ctor
X Ctor (int)
L Ctor
L Dtor
X Dtor
Y Dtor

X:
X Ctor

Y:
Y Ctor
Y Dtor

M:
X Ctor

N:
Y Ctor
X Ctor
Y Dtor

J:
Y Ctor
X Ctor

K:
K Ctor
Y Ctor
X Ctor
*/
