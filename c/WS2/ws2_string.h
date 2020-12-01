/****************************************************************************
This file was written by anat Wax on the week starting on Fabruary 2nd 2020.
This file is for function declarations only.
****************************************************************************/

size_t Strlen(char *s);

int Strcmp(const char *s1, const char *s2);      

char *Strcpy(char *dest, const char *src);

char *Strncpy(char *dest, const char *src, size_t n);

int Strcasecmp(const char *s1, const char *s2);

char *Strchr(char *str, int character);

char *Strdup(char *source);

char *Strcat(char *dest, const char *src);

char *Strncat(char *dest, const char *src, size_t n);

char *Strstr(const char *string, const char *search_str);

char Strspn(const char *s, const char *accept);

char *Strtok(char *str, const char *delim);

int IsPalindrome(const char *str);

char *add_num(const char *num1, const char *num2);

void WS2_strrev(char *str);

void SEVEN_BOOM(int from, int to);

int has_seven(int number);

void RmSpaces(char *str);

void swap_pointers_pointers(int **pp1, int **pp2);
