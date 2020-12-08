#include <stdio.h>
#include <string.h>

void SEVEN_BOOM(int from, int to);
int has_seven(int number);

int main()
{
	
	int from = 0;
	int to = 700;
	SEVEN_BOOM(from, to);

	return 0;
}

void SEVEN_BOOM(int from, int to)
{	
	int number = 0;
	for(number = from ; number < to ; ++number)
	{
		if(((number % 7) == 0) || has_seven(number))
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n", number);
		}
	}
}
	
int has_seven(int number)
{
	while(number > 0)
	{
		if(number % 10 == 7)
		{
			return 1;
		}
		else
		{
			number /= 10;
		}
	}
	return 0;
}
