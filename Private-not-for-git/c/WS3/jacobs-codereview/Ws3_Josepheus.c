#include <stdio.h>
#include <stdlib.h>


/* create array of living soldiers */
char *Circle_Of_Soldiers(char *arr, int len);

/* function that defies luck*/
int josephus(int amount);

/*   function that loops through an array to find */
/*			a victim and return next killer.	 */
/*		returns i - the next potential killer 	*/
int kill(char *circle, int i, int amount, int *last_Sword);

int main()
{
	int num_of_soldiers = 100;
	
	printf("\nIf your one of %d soldiers ", num_of_soldiers); /*//"you are"...//*/
	printf("be number: %d or else!!!\n", josephus(num_of_soldiers));
	
	return 0;
}

char *Circle_Of_Soldiers(char *arr, int len) /*// למה אתה מאתחל את כל התאים ל-1? //*/
{
	int i = 0; /*// i is not a vaid name //*/
	
	for (; i < len; i++)
	{
		arr[i] = 1;
	}
	return arr;
}

int kill(char *circle, int i, int amount, int *last_Sword)
{
	/* loop soldiers until you find the ont to kill */		/*//"one"...//*/
	int sword = i;	/*// i is not a vaid name //*/

	/* loop on the circle until in finshed */
	for ( ; sword < amount + i; sword++) /*// add barcts areound (amount + 1), whats dies amaount mean? amaount of what? //*/
	{
		int j = (sword + 1) % amount; /* if at end loop */
		
		/* if alive kill soldier */
		if (circle[j] == 1)		   /*// j is not a vaid name //*/
		{
			circle[j] = 0; 

		/*   manage the next move on the   */
		/* circle and save the last killer */
			
			if ((i + 1) == amount)
			{
				*last_Sword = i;
				i = 0;
			}
			else
			{
				*last_Sword = i;
				i++;
			}
			return i;
		}
	}
	printf("if you got until here i failed");
	
	return 0;
}

int josephus(int amount)
{
	int last_Sword = -1; /* will save the last soldier who killed */
	int i = 0; /*// i is not a vaid name //*/
	char *circle = (char *)(malloc(amount * sizeof(char)));
	
	assert(circle != NULL);

	if (amount == 0)
	{
		printf("No soldiers no death\n");
		return 0;
	}

	circle = Circle_Of_Soldiers(circle, amount); /* make an array of soldiers */

	i = 0;
    
	while (1)
	{
		if (last_Sword == i) /* check if the circle has been finished */
		{
			return last_Sword + 1;
		}

		if (circle[i] == 0) /* if we are in a dead soldier move on */
		{
			if ((i + 1) == amount)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}
		else /* if we are in a living soldier kill the next one */
		{
			i = kill(circle, i, amount, &last_Sword);
		}
	}

	return 0;
}
