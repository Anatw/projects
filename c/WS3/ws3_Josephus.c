#include <stdlib.h>
#include <stdio.h>

void create_new_circle(int num_soldiers[], int size_soldiers, int new_sum[]);
int new_round(int new_sum[], int size_new_sum);

int main()
{
	int cell = 0;
	int num_soldiers[20] = {0};
	int new_sum[10] = {0};  /* (sum_soldiers / 2) + 1; */
	/* initislize the array num_soldiers */
	for(cell = 0; cell < 100; cell++)
	{
		num_soldiers[cell] = cell + 1;
		cell++;
	}
	cell = 0;
	
	
	/* now  want to copy he remaining alive soldirs (all that is not 0)
	into new_sum[]. */
	/*while (sizeof(new_sum) > 1)
	{*/
		create_new_circle(num_soldiers, 20, new_sum);
		new_round(new_sum, 10);

	
	printf("The last remaining soldier is soldier number %d\n", new_sum[0]);
		
	return 0;
}

/* this function clean out all the "dead" soldiers, aka all numbers equals
to '0'. */
void create_new_circle(int num_soldiers[], int size_soldiers, int new_sum[])
{
	int cell = 0;
	int index = 0;
	while(cell < (size_soldiers - 1))
	{
		if(*(num_soldiers + cell) == 0)
		{
			*(new_sum + index) = *(num_soldiers + cell);
			cell++;
			index++;
			printf("%d\n", new_sum[index]);
		}
		else
		{
			cell++;
		}
	}
	while (cell < 20)
	{
		printf("%d\n", num_soldiers[cell]);
		cell++;
	}
	return;
}

int new_round(int new_sum[], int size_new_sum)
{
	int cell = 0;
	if(size_new_sum % 2 == 0)
	{
		cell += 1;
		*(new_sum + cell) = 0;
		size_new_sum /= 2;
	}
	else
	{
		*(new_sum + cell) = 0;
		cell += 1;
		size_new_sum = (size_new_sum / 2) + 1;
	}
	
	return size_new_sum;
}


/*
void cleaning(char num_soldiers[], int sum_soldirs)
{
	int index = 0;
	for(index; index < sum_soldiers; index++)
	{
		if(array[index] == 0)
		{
			index++;
		}
		else
		{
			new_reound
		}
	}
	return;
}
*/


	/*while(cell < 100)
	{
		if(num_soldiers[cell] % 2 == 0)
		{
			num_soldiers[cell] = 0;
			cell++;
			printf("%d\n", num_soldiers[cell]);
			printf("%d\n", cell);
		}
		else
		{
			cell++;
		}
	}*/
