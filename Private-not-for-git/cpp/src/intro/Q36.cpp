#include <iostream> /* cout, cin, cerr */
using namespace std;

class X
{
public:
    virtual ~X() { cout << "X dtor " << this << endl; } // Solution1 - remove "virtual".

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

int main()
{
    X *xp = new Y[5];

    delete[] xp; // Solution2: remove "[]".

    return (0);
}

// Conclution: usr virtual visely! Making base class destructor virtual guarantees that the object of derived class is destructed properly, i.e., both base class and derived class destructors are called.
