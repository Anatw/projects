#ifndef UTILITY_H
#define UTILITY_H

typedef enum 
{
	FALSE,
	TRUE
}bool;

typedef enum
{
	ERROR = -1,
	SUCCESS = 0,
	ALLOCATION_FAILURE = 1,
	NO_MORE_ROOM = 1
}status;

#endif /* UTILITY_H */
