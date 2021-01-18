/******************************************************************************

  prints "A pressed" and "T pressed" whene A and B pressed until ESC pressed
  using if statment
  
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#define ESC 27

int main()
{
	int c = 0;
	system("stty -icanon -echo");
	
	while ((c = getchar()) != ESC)
	{
		if (c == 'A')
		{
			printf("%s\n" ,"A pressed");
		}
		else if (c == 'T')
		{
			printf("%s\n" ,"T pressed");
		}
	}

	system("stty icanon echo");	
	return 0;
}
