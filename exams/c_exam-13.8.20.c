/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <assert.h>  /* assert() */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <signal.h>  /* sig_atomic_t, kill() */
#include <stddef.h>  /* offsetof(), size_t */
#include <stdio.h>   /* printf(), size_t */
#include <stdlib.h>  /* malloc(), free(), abs(), size_t */
#include <string.h>  /* size_t, atoi(), memset() */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait() */
#include <time.h>      /* time, size_t, srand() */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */

#define BITS_IN_BYTE (8)

/*#define FIRST*/
/*#define FOUR*/
/*#define FIVE*/
/*#define SIX */
/*#define EIGHT*/
/*#define TEN*/
/*#define ELEVEN*/
/*#define TWELVE*/
/*#define THERTEEN*/
/*#define FOURTEEN*/
/*#define FIFTEEN*/

#ifdef FIRST
int FlipDigitsInNum(int num)
{
    int first_digit = 0;
    int to_digit = 10;
    int return_num = 0;

    while (num)
    {
        first_digit = num % to_digit;
        num /= to_digit;
        return_num = (return_num + first_digit) * to_digit;
    }

    return (return_num / to_digit);
}
#endif /* FIRST */

#ifdef FOUR
unsigned char MirrorByte(unsigned char byte)
{
    unsigned char begin_mask = 1;
    unsigned char end_mask = 1;
    unsigned char return_val = 0;
    int i = 0;

    end_mask <<= 7;

    for (; i < 7; ++i)
    {
        if (begin_mask & byte)
        {
            return_val = return_val | end_mask;
        }

        begin_mask <<= 1;
        end_mask >>= 1;
    }

    return (return_val);
}

/* things needed fix:
1. receieved and return (and all other values) must be unsigned!
*/
#endif /* FOUR */

#ifdef FIVE
int FlipBit(int val, unsigned int n)
{
    int mask = 1;

    mask <<= (n - 1);
    return (mask ^ val);
}
#endif /* FIVE */

#ifdef SIX
int CountBitsOn(char byte)
{
    int counter = 0;

    while (byte)
    {
        byte = byte & (byte - 1);
        ++counter;
    }

    return (counter);
}
#endif /* SIX */

#ifdef EIGHT
char RotateLeft(char byte, unsigned int nbits)
{
    nbits = nbits % BITS_IN_BYTE;

    char temp_copy = byte;
    temp_copy <<= (BITS_IN_BYTE - nbits);
    byte >>= nbits;

    return (temp_copy | byte);
}
#endif /* EIGHT */

#ifdef TEN
void Swap(int** x, int** y)
{
    int* temp = *x;
    *x = *y;
    *y = temp;
}
#endif /* TEN */

#ifdef ELEVEN
size_t Strlen(const char* string)
{
    int counter = 0;
    while (*string != '\0')
    {
        ++counter;
        ++string;
    }

    return (counter);
}

int Strcmp(const char* first, const char* second)
{
    while ('\0' != *first && '\0' != *second && *first == *second)
    {
        ++first;
        ++second;
    }

    if ('\0' == *first && '\0' == *second)
    {
        return (1);
    }

    return (0);
}

char* Strcpy(char* dest, const char* source)
{
    char* dest_begin = dest;

    while ('\0' != *source)
    {
        *dest = *source;
        ++dest;
        ++source;
    }

    *dest = '\0';

    return (dest_begin);
}

char* Strncpy(char* dest, const char* source, size_t n)
{
    char* dest_begin = dest;

    for (; n > 0; --n)
    {
        *dest = *source;
        ++dest;
        ++source;
    }

    return (dest_begin);
}

char* Strcat(char* dest, const char* source)
{
    char* dest_begin = dest;
    dest += Strlen(dest);

    while ('\0' != *source)
    {
        *dest = *source;
        ++dest;
        ++source;
    }

    *dest = '\0';

    return (dest_begin);
}

/* stuff needed fix:
1. source should be const...
2. dest should receieve a '\0' at the new end.
*/

#endif /* ELEVEN */

#ifdef TWELVE

unsigned long GetFibonacciElement(unsigned int n)
{
    if (0 == n)
    {
        return (0);
    }

    if (1 == n || 2 == n)
    {
        return (1);
    }

    return (GetFibonacciElement(n - 1) + GetFibonacciElement(n - 2));
}
#endif /* TWELVE */

#ifdef THERTEEN
char* IntToString(char return_str[], int num)
{
    /*int digit = 0;
    char to_ascii = '0';
    int i = 0;

    while (num)
    {
        digit = num % 10;
        return_str[i] = digit + to_ascii;
        ++i;
    }*/

    sprintf(return_str, "%d", num);

    return (return_str);
}
#endif /* THERTEEN */

#ifdef FOURTEEN
size_t MultByEight(int num)
{
    return (num <<= 3);
}
#endif /* FOURTEEN */

#ifdef FIFTEEN
void SwapA(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void SwapB(int* x, int* y)
{
    *x += *y;
    *y = *x - *y;
    *x -= *y;
}

void SwapC(int* x, int* y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

#endif /* FIFTEEN */

/******************************************************************************/

void PrintByte(char byte)
{
    char mask = 1;
    int i = 0;

    for (; i < 8; ++i)
    {
        if (byte & mask)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }

        mask <<= 1;
    }
}

/*void foo()
{
    char* s1 = "hello";
    char s2[] = "hello";
    char* s3 = s2;
    printf("%lu %lu %lu %lu\n", sizeof(s1), sizeof(s2), strlen(s1), strlen(s2));
    s3[0] = 'H';
    printf("%s\n", s3);
}*/

void foo()
{
    size_t array[] = {0, 1, 2, 3, 4, 5};
    size_t val = 3;
    printf("%lu\n", val[array]);
}

/******************************************************************************/

int main()
{
    foo();
#ifdef FIRST
    printf("%d\n", FlipDigitsInNum(85));
#endif /* FIRST */

#ifdef FOUR
    char byte = 8;
    PrintByte(byte);
    printf("\n");
    char result = MirrorByte(byte);
    PrintByte(result);
    printf("\n");
#endif /* FOUR */

#ifdef FIVE
    int num = 6;
    printf("%d\n", FlipBit(num, 10));
#endif /* FIVE */

#ifdef SIX
    char byte = 15;

    printf("%d\n", CountBitsOn(byte));
#endif /* SIX */

#ifdef EIGHT
    char byte = 11;
    PrintByte(byte);
    printf("\n");

    int rotated = RotateLeft(byte, 5);
    PrintByte(rotated);
    printf("\n");
#endif /* EIGHT */

#ifdef TEN
    int a = 4;
    int b = 25;
    int* x = &a;
    int* y = &b;

    printf("before:\nx->%d\ny->%d\n", *x, *y);

    Swap(&x, &y);
    printf("after:\nx->%d\ny->%d\n", *x, *y);
#endif /* TEN */

#ifdef ELEVEN

    char source[] = "hello";
    char dest[] = " gorgeous";

    printf("Strlen of source = %ld\n", Strlen(source));
    printf("Strlen of dest = %ld\n", Strlen(dest));
    printf("strings are %sequal\n", (Strcmp(source, dest) == 1) ? "" : "not ");
    Strcat(source, dest);
    printf("%s\n", source);
    /*Strcpy(dest, source);
    printf("after Strcpy: %s\n", dest);
    printf("%s\n", dest);
    Strncpy(dest, source, 2);
    printf("after Strcpy: %s\n", dest);*/

#endif /* ELEVEN */

#ifdef TWELVE

    printf("%ld\n", GetFibonacciElement(0));
#endif /* TWELVE */

#ifdef THERTEEN
    int num = 1234;
    char* string = (char*)malloc(4 * sizeof(char));
    printf("%s\n", IntToString(string, num));
#endif /* THERTEEN */

#ifdef FOURTEEN
    int num = 5;
    printf("%d\n", MultByEight(num));
#endif /* FOURTEEN */

#ifdef FIFTEEN
    int x = 8;
    int y = 99;

    printf("before:\nx = %d, y = %d\n", x, y);
    SwapA(&x, &y);
    printf("after SwapA:\nx = %d, y = %d\n", x, y);
    SwapB(&x, &y);
    printf("after SwapB:\nx = %d, y = %d\n", x, y);
    SwapC(&x, &y);
    printf("after SwapC:\nx = %d, y = %d\n", x, y);
#endif /* FIFTEEN */

    return (0);
}
