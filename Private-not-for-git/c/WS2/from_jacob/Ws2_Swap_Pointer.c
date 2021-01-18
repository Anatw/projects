/****************************************************************
*                                                               *
* swap pointers		    	                                    *
*                       	                                    *
****************************************************************/



# include <stdio.h>


void Swap_Pointers_Sqr(int **p, int **q)
{
	/*// TOO manuy new lines... //*/
	
	int *tmp = *p;
	*p = *q;
	*q = tmp;
}


int main()
{

	int a = 1;
	int b = 2;
	int *c = &a;
	int *d = &b;
	
	/*// TOO manuy new lines... //*/
	
	printf("&c = %d\n &d = %d\n", *c, *d);
	
	Swap_Pointers_Sqr(&c, &d);
	
	/*// TOO manuy new lines... //*/
	printf("&c = %d\n &d = %d\n", *c, *d);
	
	return 0;
}
