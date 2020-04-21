/*******************************************************************************
 File: calculator.h - header file	
 Author: Noffar Gil
 Reviewed by: Anat Vax
 Date: 20.4.2020                                                         	   
 ******************************************************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stddef.h> /* size_t */

/* Calculator type */
typedef struct calculator calc_t;

typedef enum
{
    CALCULATOR_SUCCESS,
    MATH_ERROR,
    SYNTAX_ERROR
} status_t;

/* 
* CalculatorIniti: initialize calculator
* Receive: max_length for the input string
* Return: pointer to calc_t
* Errors: return NULL if error occurred
*/
calc_t *CalculatorInit(size_t max_length);

/* 
* CalculatorDestroy: destroy calculator
* Receive: calc - pointer to calculator
*/
void CalculatorDestroy(calc_t *calc);

/* 
* CalculatorCalculate: calculate input string
* Receive: str - the mathematic query - made of single digits seperated by 
                 operators
           out_param_status - will receive the return status
           calc - pointer to calculator
* Return: answer as double
* Errors: out_param_status will return SUCCESS, MATH_ERROR or SYNTAX_ERROR
*/
double CalculatorCalculate(const char *str,
                           status_t *out_param_status,
                           calc_t *calc);

#endif /* CALCULATOR_H */
