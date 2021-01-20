/******************************************************************************
Josephus problem:
The player enters the number of soldiers. each soldier kill the next living soldier to his left.
The program will compute who is he last surviving soldier (Where should Josephus stand in order to live).

Writen by Anat Wax, anatwax@gmail.com February 2020.
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int JosephusLocation(int size);

int main()
{
	int num_soldiers = 14;
	
	printf("The last surviving soldier is: %d\n",
										JosephusLocation(num_soldiers));
	
	return 0;
}
	
	
int JosephusLocation(int size)
{
	int winner = 0;
	int index = 0;
	int j = 0;
	int startpoint = 2;
	int *soldiers = (int*)malloc(size * sizeof(int)); 
	
	assert(soldiers != NULL);
	
	for(index = 0 ; index < size ; ++index)			
	{									
		soldiers[index] = (index + 1);
	}
	
	index = 0;
	
	while(index < (size / 2) + 1)
	{
		if(size <= 2)
		{
			winner = soldiers[0];
			return winner;
		}
		/* Keep decreasing the circle in half in each round */
		else if(size % 2 == 0) 
		{
			for(index = 1 ; index < size ; ++index)
			{
				soldiers[index] = soldiers[2 * index];
			}
		}
		else
		{
			for(index = 0 ; index < size + 1 ; ++index)
			{
				soldiers[index] = soldiers[startpoint + (2 * index)];
			}
		}
		
		index = 0;
		size = size / 2;
	}	
}
	