/*******************************************************************************
You are given an array of length 24, where each element represents the number of
new subscribers during the corresponding hour. Implement a data structure that
efficiently supports the following: • update(hour: int, value: int): Increment
the element at index hour by value. • query(start: int, end: int): Retrieve the
number of subscribers that have signed up between start and end (inclusive).

Written by Anat Wax, anatwax@gmail.com
Created: 24.9.20
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <string.h> /* size_t, atoi(), memset() */

#define HOURS (23)

typedef struct num_subs
{
    int* num_subscribers;
    /* size_t query; */
} Num_subs;

Num_subs* Init_array()
{
    Num_subs* new_array = (Num_subs*)malloc(sizeof(Num_subs));
    if (!new_array)
    {
        printf("Error in array initialization\n");
    }
    new_array->num_subscribers = (int*)calloc(HOURS, sizeof(int));
    if (!new_array->num_subscribers)
    {
        free(new_array);
        new_array = NULL;
        printf("Error in inner array initialization\n");
    }

    return (new_array);
}

void Update(Num_subs* array, int hours, int value)
{
    if (hours < 0 || hours > 23)
    {
        printf("start/end hour is incorrect\n");
    }

    array->num_subscribers[hours] += value;
}

size_t Query(Num_subs* array, int start, int end)
{
    size_t query = 0;
    int i = 0;

    if (start < 0 || end > 23)
    {
        printf("start/end hour is incorrect\n");
    }

    /* this will also cover queries when the start and end hours is the same */
    for (i = start; i <= end; ++i)
    {
        query += array->num_subscribers[i];
    }

    return (query);
}

void Destructor(Num_subs* array)
{
    free(array->num_subscribers);
    array->num_subscribers = NULL;

    free(array);
    array = NULL;
}

int main()
{
    int hour = 5;
    int value = 20;
    Num_subs* array = Init_array();

    printf("num subs in %d AM is %d\n", hour, array->num_subscribers[hour]);
    Update(array, hour, value);
    printf("num subs in %d AM is %d\n", hour, array->num_subscribers[hour]);

    Destructor(array);

    return (0);
}
