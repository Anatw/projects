/*******************************************************************************
			  	 Written by Anat Wax
				  March 12, 2020
				Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <stdio.h> /* printf() */

#include "uid.h"

int main()
{
	Uid_t new_uid = UIDCreate();
	Uid_t new_uid2 = UIDCreate();
	Uid_t bad_uid = UIDGetBadUID();
	
	printf("pid %d\n", new_uid.pid);	
	printf("time %ld\n", new_uid.time);	
	printf("count %ld\n", new_uid.count);	
	
	printf("\npid %d\n", new_uid2.pid);	
	printf("time %ld\n", new_uid2.time);	
	printf("count %ld\n", new_uid2.count);	
	
	printf("\npid %d\n", bad_uid.pid);	
	printf("time %ld\n", bad_uid.time);	
	printf("count %ld\n", bad_uid.count);
	
	printf("\ntesting UIDIsSame (1): %d\n", UIDIsSame(new_uid, new_uid2));
	
	printf("testing UIDIsSame (0): %d\n", UIDIsSame(new_uid, new_uid));
	
	return (0);
}
