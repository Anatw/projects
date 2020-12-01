/******************************************************************************

  prints "A pressed" and "T pressed" whene A and B pressed until ESC pressed
  using switch statment
  
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#define ESC 27
#define A 65
#define T 84

typedef void(*pressedP)();

void Apressed();
void Tpressed();
void EmptyFunc();

int main()
{
	int c = 0;
	int i = 0;
	pressedP funkPtr[256];
	for (; i < 256; ++i)
	{
		funkPtr[i] = EmptyFunc;
	}
	funkPtr[A] = Apressed;
	funkPtr[T] = Tpressed;
	
	system("stty -icanon -echo");
	
	while ((c = getchar()) != ESC)
	{
		funkPtr[c]();
	}

	system("stty icanon echo");	
	return 0;
}

void Apressed()
{
	printf("%s\n" ,"A pressed");
}

void Tpressed()
{
	printf("%s\n" ,"T pressed");
}

void EmptyFunc(){}








