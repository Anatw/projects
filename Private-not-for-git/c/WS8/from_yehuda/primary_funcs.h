#ifndef PRIMARY_FUNCS_H
#define PRIMARY_FUNCS_H

/* union that holds the all the available values */
typedef union {
    int int_num;
    float float_num;
    char *string;
} values_union;

typedef struct items
{
    values_union value;                           /* values union   */
    void (*add_func)(int num, values_union *var); /* add   function */
    void (*print_func)(values_union *var);        /* print function */
    void (*clear_func)(values_union *var);        /* clear function */
} item;

/* recieve num of items, make an array of items and return  	 *
 * pointer to the first item. the items intinalized to int 0 	 */
item *MakeArray(int num_of_items);

/* recieve a pointer to an item and an int number and initialize it */
int IntInit(item *item_arr, int num);

/* recieve a pointer to an item and an float number and initialize it */
int FloatInit(item *item_arr, float num);

/* recieve a pointer to an item and a string and initialize it */
int StringInit(item *item_arr, const char *string);

/* recieve items array pointer, array length and a number, and add *
 * num to each item. returns 0 if there is no error 			   */
int AddToItems(item *item_arr, int length, int num);

/* recieve items array pointer and array length, and prints the values *
 * of each item										 				   */
int PrintItems(item *item_arr, int length);

/* recieve items array pointer and array length, and clear mallocs if  *
 * needed.											 				   */
int ClearItems(item *item_arr, int length);

#endif
