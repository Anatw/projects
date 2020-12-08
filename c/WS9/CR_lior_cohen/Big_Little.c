

#include <stdio.h>
#include <stdlib.h>

#define IS_LITTLE_ENDIAN (1 == *(unsigned char *)&(const int) {1})
#define LITTLE_BIG ("gcc -E -dM - < /dev/null |grep ENDIAN")


int IsLitOrBig(int num)
{
	unsigned int i = num;
	char *c = (char*) & i;
	
	if (*c)
	{
		printf("Little endian\n");
	}
	else
	{
		printf("Big endian\n");
	}
	printf("\n");
	
	return 0;
}


int main()
{
	int num = 1;
	
	IsLitOrBig(num);		/* Uses function */
	
	if(IS_LITTLE_ENDIAN)	/* Uses Macro */
	{
		printf("Little endian\n");	
	}
	else
	{
		printf("Big endian\n");
	}
	printf("\n");
	
	system(LITTLE_BIG);		/* Uses Macro - command to GCC */
	
	return (0);
}
