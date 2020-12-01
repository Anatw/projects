/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h> /* assert() */
#include <stddef.h> /* offsetof(), size_t */
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <time.h>   /* time, size_t, srand() */
#include <unistd.h> /* ssize_t, sleep(), execvp(), fork() */

typedef unsigned char byte;
typedef size_t word;

void* Memset(void* dest, int charac, size_t n)
{
    char* byte_size = (char*)dest; /* moving in byte size */
    size_t* word_size = NULL;
    byte c_word = c & 0xff;
    word c_byte = c & 0xff;
    int i = 0;

    for (i = 0; i < 8; ++i)
    {
        c_word |= c_word << (1 << index);
    }
}

int main()
{

    return (0);
}
