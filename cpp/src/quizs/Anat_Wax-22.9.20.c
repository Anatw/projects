/*******************************************************************************
Given a string with repeated characters, rearrange the string so that no two
adjacent characters are the same. If this is not possible, return None. For
example, given "aaabbc", you could return "ababac". Given "aaab", return None.
* 1st phase – just find out T/F whether its possible
* 2nd phase - T ? (find a permutation) : (return none)


Written by Anat Wax, anatwax@gmail.com
Created: 22.9.20
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

/*
Psaudo:
 - count the occurences of every letter
 - check if the letter that appear the most has occurences that are equal to
half or half-1 of the amount of characters in the string - if not, return NULL;
 - rearrange the string  according to the requirements and return

*/

#define ASCII (255)

char* Abanibi(unsigned char* str, size_t len)
{
    size_t i = 0;
    size_t j = 0;
    size_t counter[ASCII] = {0};
    size_t temp_max = 0;
    unsigned char temp_char = 0;
    char* return_str = (char*)malloc(sizeof(char) * len);
    size_t half_len = len / 2;

    for (i = 0; i < len; ++i)
    {
        ++counter[str[i]];

        if (temp_max < counter[str[i]])
        {
            temp_max = counter[str[i]];
            temp_char = str[i];
        }
    }

    i = 0;

    if (temp_max == half_len) /* Should start with temp_char */
    {
        while (i < len)
        {
            if (j == temp_char)
            {
                ++j;
            }

            if (counter[j] > 0)
            {
                return_str[i++] = temp_char;
                --counter[temp_char];

                return_str[i++] = j;
                --counter[j];
            }
            else /* (counter[j] == 0) */
            {
                ++j;
            }
        }

        return (return_str);
    }

    return (NULL);
}

int main()
{
    char* str = "aabbbbcf";
    size_t len = strlen(str);
    char* result = Abanibi((unsigned char*)str, len);

    if (result)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("none...\n");
    }

    return (0);
}
