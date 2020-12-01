#include <iostream> /* cout, cin, cerr */

template<typename T>
void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

template<>
void foo<int>(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

int main()
{
    foo(4.2);
    foo(5);
    foo<int>(5);

    return (0);
}

