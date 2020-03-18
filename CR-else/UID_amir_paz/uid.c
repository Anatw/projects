
/*************************************************
 * File: uid.h - UID creator tests               *
 * Author: Amir paz                              *
 * Reviewed by: Anat Wax     	                 *
 * Date: 12.3.2020	                             *
 *************************************************/

#include <unistd.h> /* getpid */

#include "uid.h"

Uid_t UIDCreate()
{
	Uid_t new_uid;
	static size_t count = 0;

	/* get current proccess pid */
	new_uid.pid = getpid();

	/* get current time (the seconds past since 1.1.1970) */
	new_uid.time = time(NULL);
	new_uid.count = count;

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
