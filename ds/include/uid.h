/*******************************************************************************
This program is a UID generator - it create unique UID numbers using function
to reteiene the pid, time and a counter in case the computer send more than
one UID in the exact time.
			  	
			  	 Written by Anat Wax
				  March 12, 2020
			     Reviewer: Yaacov Evenchik
*******************************************************************************/
#ifndef UID_H
#define UID_H

#include <sys/types.h> /* pid_t */
#include <time.h> /* time() */
#include <unistd.h> /* getpid() */
#include <pthread.h> /* pthread_t, pthread_create(), ptherad_mutex_t, pthread_mutex_init(), pthread_mutex_unlock() */


typedef struct uid
{
	pid_t pid;
	time_t time;
	size_t count;
	/*pthread_mutex_t lock;*/
} Uid_t;

/* Create a new UID.
 * Return: a uid_t of the new UID.
 * Complexity: O(1). */
Uid_t UIDCreate();

/* Create a new BAD UID (all member values are 0's).
 * Return: a uid_t of the bad UID.
 * Complexity: O(1). */
Uid_t UIDGetBadUID();

/* Cech if two UIDs are equal.
 * First - a UID_t to compare.
 * First - another UID_t to compare.
 * Return: 1 if equal, 0 if different.
 * Complexity: O(1). */
int UIDIsSame(Uid_t first, Uid_t second);

#endif /* UID_H */
