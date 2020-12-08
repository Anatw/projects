#include <iostream> /* cout, cin, cerr */

void Foo(const double& x)
{
    std::cout << &x << "\n"; //0x7fffe62de670
    std::cout << x << "\n"; //5
}

void Bar(double& x)
{
    std::cout << &x << "\n"; //0x7fffe62de66c
    std::cout << x << "\n"; //2.47033e-323
}

int main()
{
    //const double a = 2;
    //double &b = a;
    int i = 5;
    Foo(i);
    Bar(reinterpret_cast<double&>(i));

    return (0);
}

