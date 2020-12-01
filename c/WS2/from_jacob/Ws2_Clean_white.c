/****************************************************************
*                                                               *
* clean white space from string start and end                   *
* and remove duplicates    	                                    *
****************************************************************/
 #include <stdio.h>
 #include <string.h>
 #include <ctype.h>
 
 void Clean_String(char *str)
 {
 	int str_leng = strlen(str) - 1;
 	char *end = str+(str_leng); /*// spaces arround + //*/
 	char *start = str;
 	int i = 0;
 	
 	while(isspace(*end))
 	{
		end--;
	}
	
	*(end + 1) = '\0'; 	   
 	
 	while(isspace(*start))
 	{
		start++;
	}
	
	strcpy(str, start);
	
	while(*str)
	{ 	
 		if(isspace(*str))
 		{
 			i = 0;
 			while(isspace(*(str+1))) /*// spaces arround + //*/
 			{
 				i++;
 				str++; 
 			}
 			/*// unneeded space //*/
 			strcpy((str - i), str);
 		}
 		str++;
 	}
 }
 
 
 int main()
 {	/*// indentation needed for the content of main //*/
 char str[] = " 	wow  this  is	  wounderful  ";

 Clean_String(str);

 printf("%s\n", str);
 
 return 0;
 }
