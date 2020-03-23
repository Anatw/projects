/******************************************************************************/
/* 						UID Implementation 							 		  */
/*						Description - Create and Compare UID's  			  */
/*						Autor - Dean Oron									  */
/*						Date - 09.03.20									      */
/*						Reviewer - Esti										  */
/*						Open Lab 86											  */
/******************************************************************************/

#ifndef UID_H
#define UID_H 

#include <sys/types.h>
#include <time.h>

struct uid
{
	pid_t pid;
	time_t time;
	int SN;
};

typedef struct uid Uid_t;

/* 
* UID Create: create new and uniqe UID		
* Return: new and uniqe UID struct 		    	  
* Time Complexity: O(1) 
*/
Uid_t UIDCreate();

/* 
* UID Get Bad: create a 'bad' (zero) UID	
* Return: new 'bad' UID struct 		    	  
* Time Complexity: O(1) 
*/
Uid_t UIDGetBadUID();

/* 
* 	UIDIsSame: check if uid1 and uid2 are the same
* 	Recieve: 2 Uid_t uid1 and uid2 to check if they are the same
* 	Return: 1 if the uids are same, 0 if not
* 	Time Complexity: O(1) 
*/
int UIDIsSame(Uid_t first, Uid_t second);

#endif /* UID_H */
