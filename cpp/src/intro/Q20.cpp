#include <iostream>

struct X
{
    //Initialization function without parameters is named DEFAULT CONSTRUCTOR (often abbreviated as: Ctor):
    explicit X();
    //Regular (non default) Ctor:
    explicit X(int a_, int b_ = 8);
    //Deinitialization function is called DESTRUCTOR (Dtor):
    ~X();
    //Copy initialization function is called copy constructor or CCtor:
    X(const X& other_); 
    //assignment operator:
    X& operator=(const X& other_);

    int m_a;
    const int m_b;
};

//Implementation of the default Ctor. Why the X::X? the code after the colon is called an INITIALIZATION LIST:
X::X(): m_a(3), m_b(4)
{
    // m_a = 3;
    // m_b = 4;
    std::cout << "this:" << this <<
                " X default Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

//Implementation of the second Ctor:
X::X(int a_, int b_): m_a(a_), m_b(b_) 
{
    std::cout << "this:" << this <<
                " X int int Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

//Implementation of the copy Ctor:
X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) 
{
    std::cout << "this:" << this <<
                " X copy Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
    m_a= other_.m_a;
    // m_b= other_.m_b;
    std::cout << "this:" << this <<
                " X assignment operator. m_a:" << m_a <<
                " does not change m_b:" << m_b << std::endl;
    
    return *this;
}

X::~X()
{
std::cout << "this:" << this <<
            " X Dtor. m_a:" << m_a <<
            " m_b:" << m_b << std::endl;
}

int main()
{
    X x1;               // default Ctor + ~x
    X x2(7);            // second Ctor + ~x
    X *px = new X(x2);  // copy Ctor + ~x
    X x3(9, 10);        // second Ctor + ~x
    X x4(x1);           // copy Ctor + ~x

    x1 = x3;            // const X& other_

    delete px; px = 0; // ~X

    X *xp = new X[10];
    delete[] xp;

    return (0);
}