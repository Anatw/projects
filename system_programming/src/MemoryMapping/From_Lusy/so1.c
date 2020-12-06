/* shared load-time */

#include "libso1.h"

void Bar1(void)
{
	puts("Your in dynamic librarry libso1 calling foo1:");

	foo1();
	
	printf("Bar1 address:   %p\n", (void *)((size_t)Bar1));
}





