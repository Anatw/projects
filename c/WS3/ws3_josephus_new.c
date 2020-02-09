#include <stdlib.h>
#include <stdio.h>

int main()
{
	int cell = 0;
	int num_soldiers[20] = {0};
	int size = 20;
	/* initislize the array num_soldiers */
	for(cell = 0; cell < 100; cell++)
	{
		num_soldiers[cell] = cell + 1;
		cell++;
	}
	/* if the number of soldiers is odd, the first soldiers in the new round
	will die first */
	if(size % 2 != 0)
	{
		num_soldiers[0] = 0;
	}
	
	while(cell < size)
	{
		num_soldiers[
	}
	
	return 0;
}
