/************************************************************
	          
*            declretion function logger WS5 	           	*
		
*					write : amir paz                        *
					review : Anat
					date : 13/02/20							
*															*
*************************************************************/

#ifndef _LOGGER_

#define _LOGGER_

typedef enum {GETOUT,COUNT, ADDUP,ADDEND,ERASE} opera;


/* Defining struct of three types */
typedef struct Logger
{
	char check[10];
	opera (*Compare)(char *str, char *filename);
	opera (*Operation)(char *str, char *filename);
} Logger;

/* Deletes a file if needs to */
opera Delete(char *, char *);

opera OperationDelete(char *, char *);

/* Counts the lines in the file if needs to */
opera Count(char *, char *);

opera OperationCountLines(char *, char *);

/* Closes the file and goes out */
opera Exit(char *, char *);

opera OperationExit(char *, char *);

/* Adds the new information to the top of the file */
opera AddBeggin(char *, char *);

opera OperationAddBeggin(char *, char *);

/* Adds the new information at the end of the file */
opera Append(char *, char *);

opera OperationAppend(char *, char *);


#endif





