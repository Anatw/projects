/*******************************************************************************
Implementation of a calculater which can calculate (only) single-digit numbers,
and only positive numbers. the calculator can handle the mathematical
operations: +, -, *, /, ^, (, ). The mathematical question will be entered to
the calculator in a form of a string.
In case of an error the calaulator resault will be 0, and a code with the 
specific error will be saved in the status_t variable.

					  		 Written by Anat Wax
						    19-21 of April, 2020
							Reviewer: Lior Cohen
*******************************************************************************/
#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef struct calculator calc_t;

typedef enum 
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR
} status_t;

/*
 * initialized the calculator by creating a map to the different inputs avaliable.
 * return: pointer to the new calculator.
 * Arguments: max_length - the maximum length the user can enter to
 *            the calculator.
 * Compexity: O(1)
 */
calc_t *CalculatorInit(size_t max_length);

/*
 * free all element connected to the calculator.
 * Arguments: calc - calculator to destroy.
 * Compexity: O(1)
 */
void CalculatorDestroy(calc_t *calc);

/*
 * return: the result of the mathematical calculation requested. In case of an
 * 		   error (syntax/mathematical), calculator will return '0'.
 * Arguments: str - string to calculate.
 *            out_param_status - pointer to the exit status from the operation -
 *                               can return: success or error (1. mathematical /
 *                               2. syntax).
 *            calc - pointer to the calculater to calculate result in.
 * Compexity: O(n)
 */
double CalculatorCalculate(const char *str, status_t *out_param_status,
                           calc_t *calc);


#endif /* CALCULATOR_H */