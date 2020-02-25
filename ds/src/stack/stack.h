/* This data structure policy is LIFO. */

typedef struck stack
{
	*
}stack_t;

/* vreate the stack */
char *StackCreate(int size);

/* free the memory of the sack */
void *StackDestroy(char *stack);

/* push an element to the first cel in the stack */
void StackPush(int *value);

/* pop the firs element in the stack */
void StackPop(int *value);

stack_t StackPeak(int *value);

int StackSize(char *stack);

void StackIsEmpty(char *stack);

