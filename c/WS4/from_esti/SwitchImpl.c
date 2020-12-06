/******************************************************************************

  prints "A pressed" and "T pressed" whene A and B pressed until ESC pressed
  using switch statment
  
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
		switch (c)
		{
		case 'A': printf("%s\n" ,"A pressed");
			break;
		case 'T': printf("%s\n" ,"T pressed");
			break;
		default:
			break;	
		}
	}

	system("stty icanon echo");	
	return 0;
}
