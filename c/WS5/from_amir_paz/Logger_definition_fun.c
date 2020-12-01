/************************************************************
	          
*            defnition function logger WS5 	                *	
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


opera OperationDelete(char *str, char *filename)
{
	remove(filename);	/* Deleting the file given	*/
	return (GETOUT);	
}

opera OperationCountLines(char *str, char *filename)
{	
	int count = 0;
	char c = 0;
	FILE *fp;
	
	fp = fopen(filename, "r");	/* Opening the file to count in it */

	for (c = getc(fp); c != EOF; c = getc(fp)) /* Turning c into the next */
	{										  
        if (c == '\n')	  /* newline */
		{
			count = count + 1;
		}
	}
	
	printf("Number of lines is: %d\n", count);

	return COUNT;
}

opera OperationExit(char *str, char *filename)
{
	return GETOUT;		/* Return "0" enum */
}

opera OperationAddBeggin(char *str, char *filename)
{
	int c = 0;
	int length = strlen(str);
	int i = 0;
	
	FILE *fp;
	FILE *fp_temp;		/* Creating a temp file to use during the process */
	
	for(i = 0 ; i < length - 1 ; ++i)
	{
		str[i] = str[i + 1];
	}
	str[length - 1] = '\0';
	
	fp = fopen(filename, "r+");
	fp_temp = fopen("temp.txt", "a+");

	fwrite(str, strlen(str), 1, fp_temp); /* Writing into the temp file	 */

	c = fgetc(fp);					/* Getting the information from our	 */
									/* file and putting it into the temp */
	while(c != EOF)					/* file								 */
	{
		fputc(c, fp_temp);
		c = getc(fp);
	}

	fseek(fp, 0, SEEK_SET);			/* Bringing the offset of both files */
	fseek(fp_temp, 0, SEEK_SET);	/*  begining of the file */

	c = fgetc(fp_temp);				/* Getting from the	temp file to fp */
									
	while(c != EOF)					
	{
		fputc(c, fp);
		c = getc(fp_temp);
	}

	remove("temp.txt");				/* Deleting the temp file	*/

	fclose(fp);
	
	return ADDUP;
}

opera OperationAppend(char *str, char *filename)
{
	FILE *fp = fopen(filename, "a+");
	
	fprintf(fp, "%s", str);
	fseek(fp, 0, SEEK_SET);		/* Bringing the offset to the begining of */
								/* the file								  */
	return ADDUP;
}


opera Delete(char *str, char *filename)
{	
	int length = strlen(str);	/* Removing the '\n' from the end of the */
	char check[] = "-remove";	/* string to make a good comparison		 */
	str[length - 1] = '\0';
	
	if(strcmp(str, check) == 0)
	{
		return ((*OperationDelete)(str, filename));
	}
	
	else
	{
		str[length -1] = '\n';	/* Returning the '\n' to the string		*/
								/* for future purposes					*/
		return ((*Count)(str, filename));	
	}
}


opera Count(char *str, char *filename)
{
	int length = strlen(str);
	char check[] = "-count";
	str[length - 1] = '\0';
	
	if(strcmp(str, check) == 0)
	{
		return ((*OperationCountLines)(str, filename));
	}
	
	else
	{
		str[length -1] = '\n';
		
		return ((*Exit)(str, filename));
	}
}


opera Exit(char *str, char *filename)
{
	int length = strlen(str);
	char check[] = "-exit";
	str[length - 1] = '\0';
	
	if(strcmp(str, check) == 0)
	{
		return (OperationExit(str, filename));
	}
	
	else
	{	
		str[length -1] = '\n';
		
		return (AddBeggin(str, filename));
	}
}

opera AddBeggin(char *str, char *filename)
{	
	if(*str == '<')	/* Checing if the first note is '<' */
	{
		return (OperationAddBeggin(str, filename));
	}
	
	else
	{
		return (Append(str, filename));
	}
}

opera Append(char *str, char *filename) /* If nothing else happened */
{
	return (OperationAppend(str, filename));
}



