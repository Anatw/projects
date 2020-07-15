#include <stdio.h>

#define CHAR_BIT (8)

int leftRotate(char n, unsigned int d)
{
    unsigned int move = d % CHAR_BIT;
    char temp = n;

    n <<= move;
    temp >>= CHAR_BIT - move;
    n |= temp;

    return (n);
}

int main()
{
    char num = 9;

    printf("%d\n", num);
    printf("%d\n", leftRotate(num, 2));

    return 0;
}



/*
int leftRotate(int n, unsigned int d) 
{ 
   return (n << d)|(n >> (INT_BITS - d)); 
} 
*/
