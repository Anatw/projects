/****************************************************************
*                                                               *
* String.h headers       	                                    *
*                       	                                    *
****************************************************************/


/* check string length */
int Ws2_Strlen(const char *str);

/* compare 2 strings return differnce in ascii */
int Ws2_Strcmp(const char *str1, const char *str2);

/* copy one string into the other */
char *Ws2_Strcpy(char *destination, const char *source);

/* copy one string into the other until char num n*/
char *Ws2_Strncpy(char *destination, const char *source, size_t n);

/* compare 2 strings return differnce in ascii ignore case*/
int Ws2_Strcasecmp(const char *str1, const char *str2);

/* search char in string return first accurance */
const char *Ws2_Strchr(const char *str, int c);

/* duplicate inserted string and returns duplication */
char *Ws2_Strdup(const char *str);

/* cat src into dest without overiding dest */
char *Ws2_Strcat(char *dest, const char *src);

/* cat src into dest without overiding dest upto char num n */
char *Ws2_Strncat(char *dest, const char *src, size_t n);

/* search string (str2) in string (str1) return first accurance */
char *Ws2_Strstr(const char *str1, const char *str2);

/* search string (str2) in string (str1) 
return num of char that correspond from str1 */
size_t Ws2_Strspn(const char *str1, const char *str2);

/*  */
char *Ws2_Strtok(char *str, const char *delim);
