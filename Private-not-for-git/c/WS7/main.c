#include <stdio.h>
#include "g.h"


int main()
{
	printf("%d\n", g_s);
	Foo(g_s);
	printf("%d\n", g_s);
	
	return (0);
}
