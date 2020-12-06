/************************************************************************
 * File: flipper_2.c													*
 *																		*
 * Purpose: A program that recieves an integer and flips it.          	*
 ************************************************************************/

#include <stdio.h>

int flip(int num);

int main()
{
    int num = 0;
    printf("Enter a number to flip! ");
    scanf("%d", &num);
    printf("\nIt is flipped! %d\n", flip(num));
    return 0;
}

int flip(int num)
{
    int result = 0;
    while (0 != num)
    {
        result *= 10;
        result += (num % 10);
        num /= 10;
    }
    return (result);
}