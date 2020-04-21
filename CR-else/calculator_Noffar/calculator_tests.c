/*******************************************************************************
 File: calculator_tests.c - tests file		
 Author: Noffar Gil                  
 Reviewed by: Anat Wax		   	   
 Date: 20.4.2020                                                         	   
 ******************************************************************************/

#include <stdio.h>	/* printf()                 */
#include <stdlib.h> /* system(), EXIT_SUCCESS	*/
#include <time.h>	/* time_t					*/
#include <assert.h> /* assert					*/

#include "calculator.h"

static int Tester(double actual_value, double expected_value, char *str, int line);
static int TestCalc(void);
static int BasicTest();

int main(void)
{
	int err_sum = 0;
	assert(BasicTest() == 0);

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

static int BasicTest()
{
	calc_t *calc = CalculatorInit(100);

	CalculatorDestroy(calc);

	return (0);
}

static int TestCalc(void)
{
	int count_errs = 0;
	calc_t *calc = CalculatorInit(100);
	status_t i = CALCULATOR_SUCCESS;
	double result = 0;
	char str[100] = "7+8";				 /* Result = 15 status = CALCULATOR_SUCCESS 	  */
	char str2[100] = "8+8*3+2^5";		 /* Result =  64 status = CALCULATOR_SUCCESS	  */
	char str3[100] = "8+8*3-2^";		 /* Result =  0 status = SYNTAX_ERROR */
	char str4[100] = "2/0";				 /* Result =  0 status = MATH_ERROR   */
	char str5[100] = "8+8*((3-2)*5)";	 /* Result = 48 status = CALCULATOR_SUCCESS 	  */
	char str6[100] = "3-2)*5";			 /* Result =  0 status = SYNTAX_ERROR */
	char str7[100] = "(3-2)*5+5*(4+4+4"; /* Result =  0 status = SYNTAX_ERROR */
	char str8[100] = "6^(3-5)";			 /* Result =  0.027778 status = CALCULATOR_SUCCESS */
	char str9[100] = "6()";				 /* Result =  0 status = SYNTAX_ERROR */
	char str10[100] = "(6^(3-5))*6+6";	 /* Result =  6.166666 status = CALCULATOR_SUCCESS */
	char str11[100] = "6*(5-3h)";		 /* Result =  0 status = SYNTAX_ERROR */
	char str12[100] = "*(5-3)";			 /* Result =  0 status = SYNTAX_ERROR */
	char str13[100] = "2+1+(2+2*2^3)";	 /* Result =  21 status = CALCULATOR_SUCCESS */


	result = CalculatorCalculate(str, &i, calc);
	count_errs += Tester(result, 15, "Test 1 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 1 status: ", __LINE__);

	result = CalculatorCalculate(str2, &i, calc);
	count_errs += Tester(result, 64, "Test 2 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 2 status: ", __LINE__);

	result = CalculatorCalculate(str3, &i, calc);
	count_errs += Tester(result, 0, "Test 3 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 3 status: ", __LINE__);

	result = CalculatorCalculate(str4, &i, calc);
	count_errs += Tester(result, 0, "Test 4 result: ", __LINE__);
	count_errs += Tester(i, MATH_ERROR, "Test 4 status: ", __LINE__);

	result = CalculatorCalculate(str5, &i, calc);
	count_errs += Tester(result, 48, "Test 5 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 5 status: ", __LINE__);

	result = CalculatorCalculate(str6, &i, calc);
	count_errs += Tester(result, 0, "Test 6 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 6 status: ", __LINE__);

	result = CalculatorCalculate(str7, &i, calc);
	count_errs += Tester(result, 0, "Test 7 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 7 status: ", __LINE__);

	result = CalculatorCalculate(str8, &i, calc);
	count_errs += Tester(result, 0.027777777777777776, "Test 8 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 8 status: ", __LINE__);

	result = CalculatorCalculate(str9, &i, calc);
	count_errs += Tester(result, 0, "Test 9 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 9 status: ", __LINE__);

	result = CalculatorCalculate(str10, &i, calc);
	count_errs += Tester(result, 6.166666666666667, "Test 10 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 10 status: ", __LINE__);

	result = CalculatorCalculate(str11, &i, calc);
	count_errs += Tester(result, 0, "Test 11 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 11 status: ", __LINE__);

	result = CalculatorCalculate(str12, &i, calc);
	count_errs += Tester(result, 0, "Test 12 result: ", __LINE__);
	count_errs += Tester(i, SYNTAX_ERROR, "Test 12 status: ", __LINE__);

	result = CalculatorCalculate(str13, &i, calc);
	count_errs += Tester(result, 21, "Test 13 result: ", __LINE__);
	count_errs += Tester(i, CALCULATOR_SUCCESS, "Test 13 status: ", __LINE__);

	CalculatorDestroy(calc);

	return (count_errs);
}

static int Tester(double actual_value, double expected_value, char *str, int line)
{
	if (actual_value != expected_value)
	{
		printf("function: %s  in line: %d ", str, line);
		printf("- status: fail... expected value was %f and actual\
		 value is %f\n",
			   expected_value, actual_value);
		puts("");

		return (1);
	}

	return (0);
}
