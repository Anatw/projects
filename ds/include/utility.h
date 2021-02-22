#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h> /* printf(), size_t */
#include <stdlib.h> /* malloc(), free(), abs() */

#define FREE(x) ((free(x), (x = NULL)))
/* to use on unused parameters: */
#define UNUSED(x) (void)(x)
#define ASCII_RANGE (256)

void PrintArray(int array[], size_t num_elements);
void Swap(int *a, int *b);
int IntCmpFunc(const void *first, const void *second);

#endif /* UTILITY_H */