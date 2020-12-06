#include <iostream> /* cout, cin, cerr */

int main()
{
    char i = 8;
    char &ip = i;
    ip = 9;
    std::cout << sizeof(ip) << std::endl;

    return (0);
}

/*
ref address: 0x7ffc81b831f8
i address: 0x7ffc08071878
*/