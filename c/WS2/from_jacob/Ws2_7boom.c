/****************************************************************
*                                                               *
* Seven_Boom function     	                                    *
*                       	                                    *
****************************************************************/
#include <stdio.h>

int Check_Digit(int num);
int Seven_Boom(int start, int end)
{
	int i = start;
	int check = 0;
	
	for(i = start; i < end + 1; i++)
	{
		if(i % 7 == 0)
		{
			printf("BOOM\n");
		}
		else
		{
			check = Check_Digit(i);
			
			if(check == 1)
			{
				printf("BOOM\n");
			}
			else
			{
				printf("%d\n", i);
			}
		}
	}
	return 0;
}

int Check_Digit(int num)
{
	int i = num;
 
 	if(num < 0)
 	{
 		i *= -1;  /*//add parentheses for (-1)//*/
 	}
 	
 	while(i > 0)
 	{
 		if(i % 10 == 7)
 		{
 			return 1;
 		}
 		i /= 10; 	
 	}
	return 0;
}



int main()
{
 Seven_Boom(0, 100);
return 0;
}
