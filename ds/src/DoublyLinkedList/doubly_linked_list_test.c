#include <stdio.h>

#include "doubly_linked_list.h"

int main()
{
	dll_t *new_list = DLLCreate();
	
	DLLDestroy(new_list);
	
	return (0);
}
