/******************************************************************************
This game accept number of soldiers. each soldier kill the nex living soldier.
The program will compute who is he last surviving soldier.

Writen by Anat Wax, February 2020. Code review was done by Lucy Volkov.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int FindWinner(int size);

int main()
{
	int size = 100; /* size = number of soldiers in the circle */
	
	printf("The last surviving soldier is: %d\n", FindWinner(size));
	
	return 0;
}
	
	
int FindWinner(int size)
{
	int winner = 0;				/* Will give the number of the last one */
	int index = 0;
	int j = 0;
	int startpoint = 2;
	int *soldiers = (int*)(malloc(size * sizeof(int))); 
	/* type casting of malloc to pointer to int */
	
	assert(soldiers != NULL);
	
	/* filling every "cell" in the array with a number [0]=1, [1]=2...: */
	for(index = 0 ; index < size ; ++index)			
	{									
		soldiers[index] = (index + 1);
	}
	
	index = 0;
	
	while(index < (size / 2) + 1)
	{
		if(size <= 2) /*this is the end of th game */
		{
			winner = soldiers[0];
			return winner;
		}
		
		/* kill all enm-numbered soldiers by deleting them with the odd-number
		soldiers - moving them to the beggining of the array: */
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
	
	
	
