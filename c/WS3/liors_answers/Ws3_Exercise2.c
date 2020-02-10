#include <stdio.h>
#include <stdlib.h>

int Ws3_Josephus(int size)
{
	int soldier = 0;				/* Will give the number of the last one */
	int i = 0;
	int j = 0;
	int startpoint = 2;
	int *soldiers  = (int*) (malloc(size * sizeof(int)));
	
	assert(soldiers != NULL);
	
	for(i = 0 ; i < size ; ++i)			/* filling every "cell" in the		*/
	{									/* array with N number				*/
		soldiers[i] = (i + 1);
	}
	
	i = 0;
	
	while(i < (size / 2) + 1)
	{
		if(size <= 2)
		{
			soldier = soldiers[0];
			return soldier;
		}
		
		else if(size % 2 == 0)
		{
			for(i = 1 ; i < size ; ++i)
			{
				soldiers[i] = soldiers[2 * i];
			}
		}
		
		else
		{
			for(i = 0 ; i < size + 1 ; ++i)
			{
				soldiers[i] = soldiers[startpoint + (2 * i)];
			}
		}
		
		i = 0;
		size = size / 2;
	}	
}

int main()
{
	int size = 100;
	
	printf("The last one to survive is: %d\n", Ws3_Josephus(size));
	
	return 0;
}
	
	
	
	
	
