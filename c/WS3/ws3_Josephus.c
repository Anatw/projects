#include <stdlib.h>
#include <stdio.h>

void create_new_circle(int nus_soldiers[], int new_sum[]);
void new_round(int new_sum[]);

int main()
{
	int cell = 0;
	int num_soldiers[100];
	int new_sum[51] = {0};  /* (sum_soldiers / 2) + 1; */
	/* initislize the array num_soldiers */
	for(cell = 0; cell < 100; cell++)
	{
		num_soldiers[cell] = cell + 1;
	}
	
	cell = 0;
	while(cell < 101)
	{
		if(num_soldiers[cell] % 2 == 0)
		{
			num_soldiers[cell] = 0;
			cell++;
		}
		else
		{
			cell++;
		}
	}
	/* now  want to copy he remaining alive soldirs (all that is not 0)
	into new_sum[]. */
	/*while (sizeof(new_sum) > 1)
	{*/
		create_new_circle(num_soldiers, new_sum);
		new_round(new_sum);

	
	printf("The last remaining soldier is soldier number %d", num_soldiers[cell]);
		
	return 0;
}

/* this function clean out all the "dead" soldiers, aka all numbers equals
to '0'. */
void create_new_circle(int num_soldiers[], int new_sum[])
{
	int cell = 0;
	int index = 0;
	while(num_soldiers)
	{
		if(num_soldiers[cell] == 0)
		{
		cell++;
		}
		else
		{
			new_sum[index] = num_soldiers[cell];
			cell++;
			index++;
		}
	}
	return;
}

void new_round(int new_sum[])
{
	int cell = 0;
	while(new_sum)
	{
		new_sum[cell] = 0;
		cell += 2;
	}
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
