

#include <stdio.h>

#include "uid.h" 


int main()
{
	Uid_t new_uid = UIDCreate();
	Uid_t new_uid2 = UIDCreate();
	Uid_t new_uid3 = UIDGetBad();
	
	printf("\n pid %d\n", new_uid.pid);	
	printf("\n time %ld\n", new_uid.time);	
	printf("\n count %d\n", new_uid.count);	
	
	printf("\n pid %d\n", new_uid2.pid);	
	printf("\n time %ld\n", new_uid2.time);	
	printf("\n count %d\n", new_uid2.count);	
	
	printf("\n pid %d\n", new_uid3.pid);	
	printf("\n time %ld\n", new_uid3.time);	
	printf("\n count %d\n", new_uid3.count);
	
	printf("\n same test neg %d\n", UIDIsSame(new_uid, new_uid2));
	
	printf("\n same test pos %d\n", UIDIsSame(new_uid, new_uid));
	
	return (0);
}
