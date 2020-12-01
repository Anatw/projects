#include <stdlib.h>
#include <stdio.h>

int main()
{
	int cell = 0;
	int num_soldiers[11] = {0};
	int size = 11;
	/* initislize the array num_soldiers */
	
	while(cell < size - 1)
	{
		for(cell = 0; cell < size; cell++)
		{
			num_soldiers[cell] = cell + 1;
			cell++;
		}
		/* if the number of soldiers is odd, the first soldiers in the new round
		will die first */
		if(size % 2 != 0)
		{
			num_soldiers[0] = 0;
			size = (size / 2) + 1;
		}
		else
		{
			size = (size / 2);
		}
		
		cell = 0;
		if(size <= 2)
		{
			return num_soldiers[0];
		}
		
		for(cell = 1; cell < size; cell++)
		{
			if(size % 2 != 0) /* the number of soldiers is odd */
			{
				num_soldiers[cell] = num_soldiers[(cell * 2) + 2];
			}
			else
			{
				num_soldiers[cell + 1] = num_soldiers[(cell * 2) + 1];
			}
		}
	}
	printf("%d", num_soldiers[0]);
	return num_soldiers[0];
}
