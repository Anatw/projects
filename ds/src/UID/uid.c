/*******************************************************************************
			  	 Written by Anat Wax
				  March 12, 2020
				Reviewer: Yaacov Evenchik
*******************************************************************************/
#include <time.h> /* time() */
#include <unistd.h> /* getpid() */
#include <pthread.h> /* ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */
#include <stdatomic.h>

#include "uid.h"

Uid_t UIDCreate()
{
	Uid_t new_uid;
	static atomic_int count = 0;
	/*time_t current_time = time(NULL);

	if ((-1) == current_time)
	{
		return(UIDGetBadUID());
	}*/
	
	pthread_mutex_init(&new_uid.lock, NULL);

	new_uid.pid = getpid(); /* syscall(SYS_gettid); - give us the thread pid */
	new_uid.time = time(NULL); /* current_time */
	
	pthread_mutex_lock(&new_uid.lock);
	new_uid.count = count;
	pthread_mutex_unlock(&new_uid.lock);

	++count;

	return (new_uid);
}

/* This function is not functional - need to fix the pid part in the middle: */
Uid_t UIDCreateAtomic()
{
	Uid_t new_uid;
	static atomic_int count = 0;

	 /*new_uid.pid = syscall(getpid); give us the thread pid */
	new_uid.time = time(NULL);
	__sync_lock_test_and_set(&new_uid.count, count);

	++count;

	return (new_uid);
}


Uid_t UIDGetBadUID()
{
	Uid_t bad_uid;
	
	bad_uid.pid = 0;
	bad_uid.time = 0;
	bad_uid.count = 0;
	
	return (bad_uid);
}

int UIDIsSame(Uid_t first, Uid_t second)
{
	return (first.pid == second.pid &&
	    	first.time == second.time &&
	    	first.count == second.count);
}
