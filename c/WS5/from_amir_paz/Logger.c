/************************************************************
	          
*            main  function logger WS5 	                	*
		
*					write : amir paz                        *
					review : Anat
					date : 13/02/20							
*															*
*************************************************************/
#define _GNU_SOURCE			/* For the getline to work */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logger.h"

#define MAX 100

/*int func()*/

int main()
{

	FILE *fp;
	
	char filename[MAX];		/* Will get name from user */
    char *buffer = NULL;
    size_t bufsize = 0;
    int stop = -1;						/* Will be used to close the loop	 */
    
    /* Declaring the array of structers */
    Logger logArr[5];
	logArr[0].Compare = Delete;
	logArr[1].Compare = Count;
	logArr[2].Compare = Exit;
	logArr[3].Compare = AddBeggin;
	logArr[4].Compare = Append;
	
	logArr[0].Operation = OperationDelete;
	logArr[1].Operation = OperationCountLines;
	logArr[2].Operation = OperationExit;
	logArr[3].Operation = OperationAddBeggin;
	logArr[4].Operation = OperationAppend;
    
	printf("Enter file name: ");	/* Geting the file from the user and */
	scanf("%s", filename);			/* opening it. If it doesn't exist	 */
	fp = fopen(filename, "a");		/* creating it						 */
	
	/* */
	while(stop != GETOUT) /* getout = 0 in enum */				
	{	
		getline(&buffer, &bufsize, stdin); /* do malloc lonly */
		stop = (*logArr[0].Compare)(buffer, filename);/* send for the first ,ifnot Going to the next */ 
	}
	
	fclose(fp);
	free(buffer);		/* Freeing the allocated careated by getline */


	return (0);

}







