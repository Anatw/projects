/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Calc                                   #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  20-07-2017                             ##########    ####  ###  ######## 
 *  13:21:22                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <time.h>					 /* time_t						  */

#include "calc.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

static int Tester(long actual_value, long expected_value, char *str, int line);
static int TestCalc(void);

int main(void)
{
	int err_sum = 0;

	err_sum += TestCalc();
	
	if (0 == err_sum)
	{
		puts("Calculator TEST SUCCESS!!");
	}
	else
	{
		printf("found %d bugs in the program\n", err_sum);
	}
	
	return (EXIT_SUCCESS);
}

static int TestCalc(void)
{
	int count_errs = 0;
	calc_t *calc = CalcInit(100);
	status_t i = SUCCESS;
	double result = 0;
	char str[100] = "7+8"; 				 /* Result = 15 status = SUCCESS 	  */
	char str2[100] = "8+8*3+-2^5";		 /* Result =  0 status = SUCCESS	  */
	char str3[100] = "8+8*3-2^";		 /* Result =  0 status = SYNTAX_ERROR */
	char str4[100] = "2/0";				 /* Result =  0 status = MATH_ERROR   */
	char str5[100] = "8++8*((3-2)*5)";	 /* Result = 48 status = SUCCESS 	  */
	char str6[100] = "3-2)*5";			 /* Result =  0 status = SYNTAX_ERROR */
	char str7[100] = "(3-2)*5+ 5*(4+4+4";/* Result =  0 status = SYNTAX_ERROR */

	result =  CalcCalculate(str, &i, calc);
	count_errs += Tester(result, 15, "Test 1 result: ", __LINE__);
	count_errs += Tester(i, SUCCESS, "Test 1 status: ", __LINE__);


	result =  CalcCalculate(str2, &i, calc);
	count_errs += Tester(result, 0, "Test 2 result: ", __LINE__);
	count_errs += Tester(i, SUCCESS, "Test 2 status: ", __LINE__);

	
	result =  CalcCalculate(str3, &i, calc);
	count_errs += Tester(result, 0, "Test 3 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 3 status: ", __LINE__);

	
	result =  CalcCalculate(str4, &i, calc);
	count_errs += Tester(result, 0, "Test 4 result: ", __LINE__);
	count_errs += Tester(i, MATH_ERROR, "Test 4 status: ", __LINE__);


	result =  CalcCalculate(str5, &i, calc);
	count_errs += Tester(result, 48, "Test 5 result: ", __LINE__);
	count_errs += Tester(i, SUCCESS, "Test 5 status: ", __LINE__);


	result =  CalcCalculate(str6, &i, calc);
	count_errs += Tester(result, 0, "Test 6 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 6 status: ", __LINE__);
	
	result =  CalcCalculate(str7, &i, calc);
	count_errs += Tester(result, 0, "Test 7 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 7 status: ", __LINE__);
	
	CalcDestroy(calc);

	return(count_errs);
}


static int Tester(long actual_value, long expected_value, char *str, int line)
{	
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %ld and actual\
		 value is %ld\n",
				expected_value, actual_value);
		puts("");
				
		return (1);
	}
	
	return (0);
}
