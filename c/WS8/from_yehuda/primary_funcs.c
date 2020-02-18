#include <stdlib.h> /* mallac() */
#include <stdio.h>  /* printf() */
#include <string.h> /* strlen(), strcpy() */

#include "primary_funcs.h"
#include "help_funcs.h" /* all the help functions are from here */

item *MakeArray(int num_of_items)
{
    int i = 0;

    /* allocate memory for the array */
    item *arr = (item *)malloc(num_of_items * sizeof(item));

    if (NULL == arr)
    {
        printf("can't allocate memory for the array\n");
        return (NULL);
    }

    /* initialize the array as 0 int */
    for (i = 0; i < num_of_items; ++i)
    {
        arr[i].value.int_num = 0;
        arr[i].add_func = AddToInt;
        arr[i].print_func = PrintInt;
        arr[i].clear_func = ClearNothing;
    }

    return (arr);
}

int IntInit(item *item_arr, int num)
{
    if (NULL == item_arr)
    {
        printf("can't initialize int\n");
        return (0);
    }

    /* assign the value and the right functions */
    item_arr->value.int_num = num;
    item_arr->add_func = AddToInt;
    item_arr->print_func = PrintInt;
    item_arr->clear_func = ClearNothing;

    return (1);
}

int FloatInit(item *item_arr, float num)
{
    if (item_arr == NULL)
    {
        printf("can't initialize float\n");
        return (0);
    }

    /* assign the value and the right functions */
    item_arr->value.float_num = num;
    item_arr->add_func = AddToFloat;
    item_arr->print_func = PrintFloat;
    item_arr->clear_func = ClearNothing;

    return (1);
}

int StringInit(item *item_arr, const char *string)
{
    if (NULL == item_arr)
    {
        printf("can't initialize string\n");
        return (0);
    }

    /* check if the item is not new */
    if (item_arr->value.int_num != 0)
    {
        free(item_arr->value.string);
    }

    /* allocate memory for the new string */
    item_arr->value.string = (char *)malloc((sizeof(char) *
                                             strlen(string)) +
                                            1);
    if (NULL == item_arr->value.string)
    {
        printf("can't allocate memory for string\n");
        return (0);
    }

    /* assign the value and the right functions */
    strcpy(item_arr->value.string, string);
    item_arr->add_func = AddToString;
    item_arr->print_func = PrintString;
    item_arr->clear_func = ClearString;
    return (1);
}

int AddToItems(item *item_arr, int length, int num)
{
    int i = 0;

    if (item_arr[0].add_func == NULL)
    {
        printf("can't read add function\n");
        return (0);
    }

    for (i = 0; i < length; ++i)
    {
        (*item_arr[i].add_func)(num, &item_arr[i].value);
    }

    return (1);
}

int PrintItems(item *item_arr, int length)
{
    int i = 0;

    if (item_arr[0].print_func == NULL)
    {
        printf("can't read print function\n");
        return (0);
    }

    for (i = 0; i < length; ++i)
    {
        (*item_arr[i].print_func)(&item_arr[i].value);
    }

    return (1);
}

int ClearItems(item *item_arr, int length)
{
    int i = 0;

    if (item_arr[0].clear_func == NULL)
    {
        printf("can't read clear function\n");
        return (0);
    }

    /*  clear all the items */
    for (i = 0; i < length; ++i)
    {
        (*item_arr[i].clear_func)(&item_arr[i].value);
    }

    /* finally, clear the array itself */
    free(item_arr);
    item_arr = NULL;

    return (1);
}
