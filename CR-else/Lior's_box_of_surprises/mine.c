#include <stdio.h>
#include <stdlib.h> /* system() */
#include <unistd.h> /* sleep()	*/

#include "mine.h"

int ThinkOfaNum(int num)
{
	char enter[1] = {0};
	int result = num;	
	
	system("clear");
	printf("\n");
	printf("Multiply your number by 9 and press Enter when done\n");
	fgets(enter, 2, stdin);
	result *= 9;
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Subtruct 5 from the result you got and press Enter when ready\n");
	fgets(enter, 2, stdin);
	result -= 5;
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Add the digits of the number until you get a one digit number,\n");
	printf("Lets say you got 55, than 5+5=10, than 1+0=1 and 1 is the answer.\n");
	printf("Press enter when ready\n");
	fgets(enter, 2, stdin);
	result = 4;
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Turn the number you got to the alphabet English letter:\n");
	printf("1=A, 2=B and so on... Press Enter when ready\n");
	fgets(enter, 2, stdin);
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Think of a country that starts with the letter you have, for\n");
	printf("example, you got I so Israel, and press Enter when ready\n");
	fgets(enter, 2, stdin);
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("OK, now it gets a bit tricky:\n");
	printf("Think of the letter after the one you got, so lets say you got I,\n");
	printf("then think about the letter J, and press Enter when ready\n");
	fgets(enter, 2, stdin);
	
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Think of an animal that starts with that letter and press Enter\n");
	fgets(enter, 2, stdin);
	
	
	system("clear");
	printf("\n");
	enter[0] = 0;
	printf("Think of that animal color, got it? Press Enter\n");
	fgets(enter, 2, stdin);
	
	
	system("clear");
	printf("\n");
	printf("I am sorry to tell you, but there are no Grey Elephants in Denmark!\n");
	
	sleep(5);
	system("clear");
	
	return (result);
}

