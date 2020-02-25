#include <stdlib.h>

#include "stack.h"

int main()
{
	size_t stacksize = 20;
	stack_t *stack = StackCreate(stacksize);
	int value = 5;
	int *p_value = &value;
	
	printf("'stack' address is: %p\n", stack);
	
	StackPush(p_value, stack);

	return (0);
}
