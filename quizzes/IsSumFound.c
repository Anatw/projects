#include <stdlib.h>
#include <stdio.h>

int IsSumFound(int array[], int sum, int *first, int *second);

int main()
{
	int array[] = {2, 4, 7, 9, 12, 17, 21};
	int sum = 24;
	int *first = &array[0];
	int size = (sizeof(array) / sizeof(int));
	int *second = &array[size];
	IsSumFound(array, sum, first, second);
	printf("first = %d, second = %d\n", *first, *second);
	return 0;
}

int IsSumFound(int array[], int sum, int *first, int *second)
{
	int start = array[0];
	int end = array[(int)sizeof(array)];
	int addition = *(array+first) + *(array+second);
	if(addition == sum)
	{
		return 1;
	}
	if else(addition < sum)
	{
		first++;
	}
	if else(addition > sum)
	{
		second--;
	}
	else
	{
		return 0;
	}
}
