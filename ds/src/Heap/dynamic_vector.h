/*******************************************************************************
This program build a dynamic vector (dynamic array) in the capacity requested by
the user (using realloc). The user can push or pop to the top of the array, set
a specific index in the array, shrink the capacity of the array to a specific
size, reserve a specific capacity and frees all malloc.

					  	 Written by Anat Wax
						  February 27, 2020
						Reviewer: Yehuda Levavi
*******************************************************************************/

#ifndef DYMANIC_VECTOR_H
#define DYMANIC_VECTOR_H

typedef struct dynamic_vector vector_t;

/* Creates a dynamic array with a given size and return pointer to the array */
/* if the malloc failes, the function returns a NULL pointer				 */
vector_t *VectorCreate(size_t capacity);

/* Frees a given array */
void VectorDestroy(vector_t *vector);

/* Gets the capacity of the given dynamic array */
size_t VectorCapacity(vector_t *vector);

/* Gets the size of a given array */
size_t VectorSize(vector_t *vector);

/* Pushes a given element to the end of a given array */
/* 0 = success, !0 = error */
int VectorPushBack(vector_t *vector, void *value);

/* Shrinks a given array to fit its elements */
/* 0 = success, !0 = error */
int VectorShrinkToFit(vector_t *vector);

/* Removes the last element in a given array */
void VectorPopBack(vector_t *vector);

/* Sets a given element to a given array on a given index */
void VectorSetElement(vector_t *vector, int index, void *value);

/* Gets the element from a given array in a given index */
void *VectorGetElement(vector_t *vector, size_t index);

/* Resizes a given array with a given capacity & return pointer to the array */
/* 0 = success, !0 = error */
int VectorReserve(vector_t *vector, size_t capacity);

#endif
