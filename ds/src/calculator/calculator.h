#ifndef CALCULATOR_H
#define CALCULATOR_H

/*****************
 * this calculatror can calculte a string containing numbers and the
 * mathematical operations: +, -, *, /, ^, ( and ). It can handle only one-digit
 * integers, and only positive numbers.
 * ********************************/

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
 * Arguments: max_length - the 
 * Compexity: 
 */
calc_t *CalculatorInit(size_t max_length);

/*
 * free all element connected to the calculator.
 * Arguments: calc - calculator to destroy.
 * Compexity: 
 */
void CalculatorDestroy(calc_t *calc);

/*
 * return: 
 * Arguments: str - string to calculate.
 *            out_param_status - pointer to the exit status from the operation -
 *                               can return: success or error (mathematical /
 *                               operation).
 *            calc - pointer to the calculater to calculate result in.
 * Compexity: 
 */
double CalculatorCalculate(const char *str, status_t *out_param_status,
                           calc_t *calc);


#endif /* CALCULATOR_H */