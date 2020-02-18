#include <stdio.h> /* printf() */

#include "primary_funcs.h"

#define ARR_LENGTH 6

int main()
{
	/* fetch an initialized array pointer */
	item *my_arr = MakeArray(ARR_LENGTH);
	int i = 0;
	
	/* assign new elements to the array */
	IntInit(&my_arr[0], 65);
	
	FloatInit(&my_arr[1], 3.456);
	
	StringInit(&my_arr[2], "haha");
		
	IntInit(&my_arr[3], 43);
	
	FloatInit(&my_arr[4], 5.4876365);
	
	StringInit(&my_arr[5], "Yesyesyes");
	
	/* print all the items in the array */
	PrintItems(my_arr, ARR_LENGTH);
	
	printf("\n");
	for (i = 0; i < 10; i++)
	{
		/* add i + 3 to all the items */
		AddToItems(my_arr, ARR_LENGTH, i + 3);
	
		PrintItems(my_arr, ARR_LENGTH);
	
		printf("\n");
	}
	
	/* clear the array and its elements */
	ClearItems(my_arr, ARR_LENGTH);
	my_arr = NULL;
	
    return 0;
}
