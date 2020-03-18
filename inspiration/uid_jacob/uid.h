


#ifndef UID_H
#define UID_H 

#include <sys/types.h>
#include <unistd.h>
#include <time.h>

struct uid
{
	pid_t pid;
	time_t time;
	int count;
};

typedef struct uid Uid_t;


Uid_t UIDCreate();

Uid_t UIDGetBad();

int UIDIsSame(Uid_t first, Uid_t second);

#endif /* UID_H */
