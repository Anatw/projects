/*******************************************************************************
 * File: variable_size_allocation_tests.c - tests file				 		   *
 * Author: Yehuda Levavi                                                       *
 * Reviewed by: Anat Wax				                                   	   *
 * Date: 24.3.2020                                                             *
 * Note: Due to efficiency reasons, there are no user protection in the 	   *
 * functions, and all the validations are the responsibility of the user.      *
 ******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "variable_size_allocation.h"

int BasicTest();
int AdvencedTest();

int main()
{
	assert(BasicTest() == 0);
	assert(AdvencedTest() == 0);
	return (0);
}

int BasicTest()
{
	int *my_int = NULL;
	char *my_string = NULL;
	int *my_int3 = NULL;

	void *vsa_raw = malloc(220);

	vsa_t *new_vsa = VSAInit(vsa_raw, 220);

	assert(VSALargestBlockAvailable(new_vsa) == 184);

	my_int = (int *)VSAAlloc(new_vsa, 4);
	assert(VSALargestBlockAvailable(new_vsa) == 160);

	my_string = (char *)VSAAlloc(new_vsa, 7);
	assert(VSALargestBlockAvailable(new_vsa) == 136);

	my_int3 = (int *)(VSAAlloc(new_vsa, 136));
	assert(VSALargestBlockAvailable(new_vsa) == 0);

	VSAFree(my_int3);
	assert(VSALargestBlockAvailable(new_vsa) == 136);

	my_int3 = (int *)(VSAAlloc(new_vsa, 80));
	assert(VSALargestBlockAvailable(new_vsa) == 40);

	*my_int = 4;
	*my_int3 = 79;
	strcpy(my_string, "helloa");

	VSAFree(my_string);

	assert(VSALargestBlockAvailable(new_vsa) == 40);

	my_string = (char *)VSAAlloc(new_vsa, 100);
	assert(my_string == NULL);

	my_string = (char *)VSAAlloc(new_vsa, 25);
	assert(VSALargestBlockAvailable(new_vsa) == 8);

	strcpy(my_string, "helloa, I am Yehuda, ho");

	VSAFree(my_int);
	VSAFree(my_int3);
	VSAFree(my_string);

	assert(VSALargestBlockAvailable(new_vsa) == 184);

	free(vsa_raw);

	return (0);
}

int AdvencedTest()
{
	int *my_int = NULL;
	int *my_int2 = NULL;
	int *my_int3 = NULL;
	int *my_int4 = NULL;

	void *vsa_raw = malloc(220);

	vsa_t *new_vsa = VSAInit(vsa_raw, 220);

	assert(VSALargestBlockAvailable(new_vsa) == 184);

	my_int = (int *)VSAAlloc(new_vsa, 4);
	assert(VSALargestBlockAvailable(new_vsa) == 160);

	my_int2 = (int *)VSAAlloc(new_vsa, 80);
	assert(VSALargestBlockAvailable(new_vsa) == 64);

	my_int3 = (int *)(VSAAlloc(new_vsa, 4));
	assert(VSALargestBlockAvailable(new_vsa) == 40);

	my_int4 = (int *)(VSAAlloc(new_vsa, 30));
	assert(VSALargestBlockAvailable(new_vsa) == 0);

	VSAFree(my_int);
	VSAFree(my_int3);
	VSAFree(my_int4);
	assert(VSALargestBlockAvailable(new_vsa) == 64);

	my_int = (int *)(VSAAlloc(new_vsa, 20));
	assert(VSALargestBlockAvailable(new_vsa) == 24);

	my_int3 = (int *)VSAAlloc(new_vsa, 20);
	assert(VSALargestBlockAvailable(new_vsa) == 8);

	my_int4 = (int *)VSAAlloc(new_vsa, 8);
	assert(VSALargestBlockAvailable(new_vsa) == 0);

	VSAFree(my_int);
	VSAFree(my_int2);
	VSAFree(my_int3);
	VSAFree(my_int4);

	assert(VSALargestBlockAvailable(new_vsa) == 184);

	my_int = (int *)(VSAAlloc(new_vsa, 184));
	assert(VSALargestBlockAvailable(new_vsa) == 0);

	VSAFree(my_int);

	free(vsa_raw);

	return (0);
}
