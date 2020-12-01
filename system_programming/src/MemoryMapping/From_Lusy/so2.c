/* shared run-time */

#include "libso2.h"

void Bar2()
{
	puts("Your in libso2- run-time dyn lib, calling foo2:");
	
	foo2();
	
	printf("Bar2 address:   %p\n", (void *)((size_t)Bar2));
}



