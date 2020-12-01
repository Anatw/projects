#include <iostream> /* cout, cin, cerr */
using namespace std;

class X
{
public:
    ~X() { cout << "X dtor " << this << endl; } // Solution1 - remove "virtual".

private:
    double m_a;
};

class Y : public X
{
public:
    ~Y() { cout << "Y dtor " << this << endl; }

private:
    int m_b;
};

void Foo(Y y)
{
    cout << "inside Foo, this: " << endl;
}

int main()
{
    Y y1;
    Foo(y1);

    return (0);
}
