#include <iostream> /* cout, cin, cerr */

void foo(int, int i = 3, float = 4)
{
    std::cout << i;    
}

int main()
{
    foo(4, 8.7);

    return (0);
}