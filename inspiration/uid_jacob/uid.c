


#include "uid.h" 



Uid_t UIDCreate()
{
	Uid_t new_uid;
	static int count = 0;
	
	new_uid.pid = getpid();
	new_uid.time = time(NULL);
	new_uid.count = count;
	
	++count;
	
	return (new_uid);
}


Uid_t UIDGetBad()
{
	Uid_t bad_uid;
		
	bad_uid.pid = 0;
	bad_uid.time = 0;
	bad_uid.count = 0;
	
	return (bad_uid);
}


int UIDIsSame(Uid_t first, Uid_t second)
{
	if (first.pid == second.pid && first.time == second.time && first.count == second.count)
	{
		return (1);
	}

	return (0);
}
