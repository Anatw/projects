
/*******************************************************************************
From GeekForGeeks:
Swap bits in a given number
Last Updated: 11-08-2020
Given a number x and two positions (from the right side) in the binary representation of x, write a function that swaps n bits at given two positions and returns the result. It is also given that the two sets of bits do not overlap.


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 15.11.2020
Version: 1
*******************************************************************************/
#include <stdio.h> /* printf */
#include <limits.h> /* CHAR_BIT */


void PrintBits(char c)
{
    int i = 0;
    for (; i < CHAR_BIT; ++i)
    {
        printf("%d", 1 & c);
        c >>= 1;
    }

    printf("\n");
}

/*void SwapBits(char c, int first, int second)
{
    char inner_c = 0;
    char first_mask = 1;
    char second_mask = 1;

    printf("before - the letter %c: ", c);
    PrintBits(c);

    inner_c = c << (CHAR_BIT - first);

    first_mask = (1 << (CHAR_BIT - first)) & inner_c;

    inner_c = c << (CHAR_BIT - second);
    second_mask = (1 << (CHAR_BIT - second)) & inner_c;

    first_mask >>= (CHAR_BIT - second);
    second_mask >>= (CHAR_BIT - first);
    c = c ^ first_mask;
    c = c ^ second_mask;

    printf("after: ");
    PvoidrintBits(c);
}*/

/*char FlipBit(char c, int location)
{
    char mask = 1 << (CHAR_BIT - location);
    return (c ^ mask);
}
*/
char SetBit(char c, int location, char status)
{
    return (c ^= (-status ^ c) & (1UL << location));
}
/*
(-status ^ c)
Is like writing:
if (status == 1) 
{
    11111111
    11100110
^
    00011001
    00000010
    &
    00000000

    ~c;

    c = ~c;
}
else
{
    ;
}
*/

void SwapBits(char c, int first, int second)
{
    printf("before - the letter %c: \nfirst = %d\nsecond = %d\n", c, first, second);
    PrintBits(c);

    char first_status = 1;
    char second_status = 1;

    first_status = (first_status << first) & first;
    second_status = (second_status << second) & second;

    c ^= (-first_status ^ c) & (1 << second);
    c ^= (-second_status ^ c) & (1 << first);

    PrintBits(c);
    printf("12345678\n");

}

int main()
{
    char c = 'g';
    SwapBits(c, 1, 6);
    
    /*PrintBits(c);
    PrintBits(SetBit(c, 1, 1));*/
    /*PrintBits(FlipBit(c, 6));*/
    return 0;
}