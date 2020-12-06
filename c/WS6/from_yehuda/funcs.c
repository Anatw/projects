#include <stdio.h>
#include "funcs.h"

long Pow2(unsigned int x, unsigned int y)
{
    unsigned int answer = 1;
    answer <<= y;
    answer = Multiply(answer, x);
    return (answer);
}

long Multiply(unsigned int x, unsigned int y)
{
    unsigned int answer = 0;
    while (y != 0)
    {
        if (y & 1)
        {
            answer += x;
        }
        x <<= 1;
        y >>= 1;
    }
    return (answer);
}

int IsPowerOfTwoLoop(unsigned int n)
{
    while (n != 2)
    {
        if (n % (n >> 1) != 0)
        {
            return (0);
        }
        n >>= 1;
    }
    return (1);
}

int IsPowerOfTwo(unsigned int n)
{
    /* n & n-1 will always be 0. and checking n is not zero */
    return n && (!(n & (n - 1)));
}

long AddOne(unsigned int x)
{
    int m = 1;

    /* Flip all the set bits until we find a 0 */
    while (x & m)
    {
        x = x ^ m;
        m <<= 1;
    }

    /* flip the rightmost 0 bit */
    x = x ^ m;
    return x;
}

void PrintThreeBits(unsigned int *arr, int length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if (CountOnBits(arr[i]) == 3)
        {
            printf("%u, ", arr[i]);
        }
    }
    printf("\n");
}

long CountOnBits(unsigned int n)
{
    unsigned int count = 0;
    while (n)
    {
        n &= (n - 1);
        count++;
    }
    return count;
}

long ByteMirrorLoop(unsigned int num)
{
    unsigned int result = 0;
    int i = 0;

    for (i = 0; i < 8; ++i)
    {
        result <<= 1;
        if (num & 1)
        {
            result |= 1;
        }
        num >>= 1;
    }

    return result;
}

long ByteMirror(unsigned int num)
{
    unsigned int result = 0;

     if (num & 1)
    {
        result |= 128;
    }
    if (num & 2)
    {
        result |= 64;
    }
    if (num & 4)
    {
        result |= 32;
    }
    if (num & 8)
    {
        result |= 16;
    }
    if (num & 16)
    {
        result |= 8;
    }
    if (num & 32)
    {
        result |= 4;
    }
    if (num & 64)
    {
        result |= 2;
    }
    if (num & 128)
    {
        result |= 1;
    }

    return result;
}
