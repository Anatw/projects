/*******************************************************************************
Morning quizz:

Given a string in such a way that every character occurs in a repeated manner.
Your task is to print the string by inserting the frequency of each unique
character after it and also eliminating all repeated characters.

Input : HARRY
Output : H1A1R2Y
Input : ccccOddEEE
Output : c4O1d2E3
static void wordCompress(String s) {...}


Written by Anat Wax, anatwax@gmail.com
Created: 15.9.20
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

/*
Psaudo:
1. create a lut for all chars (using calloc).
2. go ober the array and increment the lut in the char cell.
iterate the lut and insert the letter and the amout it was shown.
*/

#define ASCII (255)

void PrintOccurences(const char* str)
{
    size_t length = strlen(str);
    size_t i = 0;
    size_t inner_index = 0;
    char* result = (char*)calloc(length, sizeof(char) * 2);

    int* lut = (int*)calloc(ASCII, sizeof(char));

    for (i = 0; i < length; ++i)
    {
        ++(lut[(unsigned char)str[i]]);
    }

    for (i = 0; i < length; ++i)
    {
        while (*(str + i) == *(str + i + 1))
        {
            ++i;
        }

        *(result + inner_index++) = *(str + i);
        *(result + inner_index++) = (lut[(unsigned char)str[i]] + '0');
    }

    printf("%s\n", result);
}

int main()
{
    char* str = "ccccOddEEE";

    printf("%s\n", str);
    PrintOccurences(str);

    return (0);
}
