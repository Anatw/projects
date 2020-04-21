/*******************************************************************************
 File: calculator.c - operation funcs	
 Author: Noffar Gil                                                       
 Reviewed by: Anat Wax                                   			   	   
 Date: 20.4.2020                                                         	   
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* strtod */

#include "calculator.h"
#include "stack.h"

#define ASCII_RANGE (256)

/* availbale states */
typedef enum
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	CALCULATOR_ERROR = 2,
	STATE_RANGE
} state_t;

/* operations priorities */
typedef enum
{
	NOTHING = 0,
	END = 1,
	OPEN_PAR,
	SUB,
	ADD = SUB,
	MULT,
	DIV = MULT,
	POW,
	CLOSING_PAR
} operation_priority_t;

/* state entries struct (handler + next state): */
typedef struct
{
	status_t (*handler)(char **char_ptr, calc_t *calc);
	state_t next_state;
} state_entry_t;

/* operators struct (calculator function  + operation priority) */
typedef struct
{
	status_t (*calc_func)(double *num1, double num2);
	operation_priority_t priority;
} operator_t;

/* calculator managing struct */
struct calculator
{
	state_entry_t table[STATE_RANGE][ASCII_RANGE];
	operator_t operators[ASCII_RANGE];
	stack_t *num_stack;
	stack_t *operators_stack;
};

/* basic state entries */
static status_t ErrorHandler(char **char_ptr, calc_t *calc);
static status_t NumHandler(char **char_ptr, calc_t *calc);
static status_t OperatorHandler(char **char_ptr, calc_t *calc);
static status_t OpenParHandler(char **char_ptr, calc_t *calc);
static status_t CloseParHandler(char **char_ptr, calc_t *calc);
static status_t EndHandler(char **char_ptr, calc_t *calc);



const state_entry_t error_state_entry = {ErrorHandler, CALCULATOR_ERROR};
const state_entry_t num_entered = {NumHandler, WAIT_FOR_OP};
const state_entry_t op_entered = {OperatorHandler, WAIT_FOR_NUM};
const state_entry_t open_par_entered = {OpenParHandler, WAIT_FOR_NUM};
const state_entry_t close_par_entered = {CloseParHandler, WAIT_FOR_OP};
const state_entry_t end_entered = {EndHandler, CALCULATOR_ERROR};

/* basic operations functions and structs */
static status_t Add(double *num1, double num2);
static status_t Sub(double *num1, double num2);
static status_t Mult(double *num1, double num2);
static status_t Div(double *num1, double num2);
static status_t Pow(double *num1, double num2);
static status_t EmptyFunc(double *num1, double num2);
static status_t SyntaxErrorFunc(double *num1, double num2);

const operator_t add = {Add, ADD};
const operator_t sub = {Sub, SUB};
const operator_t mult = {Mult, MULT};
const operator_t divide = {Div, DIV};
const operator_t power = {Pow, POW};
const operator_t open_par = {SyntaxErrorFunc, OPEN_PAR};
const operator_t closing_par = {SyntaxErrorFunc, CLOSING_PAR};
const operator_t first_dummy_oper = {SyntaxErrorFunc, NOTHING};
const operator_t end = {EmptyFunc, END};

static void InitLUTOper(calc_t *new_calc);
static void InitStateTable(calc_t *new_calc);

calc_t *CalculatorInit(size_t max_length)
{
	calc_t *new_calc = (calc_t *)malloc(sizeof(calc_t));

	if (new_calc == NULL)
	{
		return (NULL);
	}

	/* initialize the 2 stacks */
	new_calc->num_stack = StackCreate(max_length);
	if (new_calc->num_stack == NULL)
	{
		Free(new_calc);

		return (NULL);
	}

	new_calc->operators_stack = StackCreate(max_length);
	if (new_calc->operators_stack == NULL)
	{
		Free(new_calc->num_stack);
		Free(new_calc);

		return (NULL);
	}

	/* in order to mark start of stack- to deal with corner case of the first operator insertion */
	StackPush(new_calc->operators_stack, (void *)&first_dummy_oper);

	InitLUTOper(new_calc);
	InitStateTable(new_calc);
	
	return (new_calc);
}


static void InitLUTOper(calc_t *new_calc)
{
	int i = 0;
	/* initializing operators LUT */
	for (i = 0; i < ASCII_RANGE; ++i)
	{
		new_calc->operators[i] = first_dummy_oper;
	}

	new_calc->operators['+'] = add;
	new_calc->operators['-'] = sub;
	new_calc->operators['*'] = mult;
	new_calc->operators['/'] = divide;
	new_calc->operators['^'] = power;
	new_calc->operators['('] = open_par;
	new_calc->operators[')'] = closing_par;
	new_calc->operators['\0'] = end;
}


static void InitStateTable(calc_t *new_calc)
{
	int i = 0;
	int j = 0;
	
	/* initializing table LUT */
	for (i = 0; i < STATE_RANGE; ++i)
	{
		for (j = 0; j < ASCII_RANGE; ++j)
		{
			new_calc->table[i][j] = error_state_entry;
		}
	}

	for (i = '0'; i <= '9'; ++i)
	{
		new_calc->table[WAIT_FOR_NUM][i] = num_entered;
	}
	new_calc->table[WAIT_FOR_NUM]['('] = open_par_entered;

	new_calc->table[WAIT_FOR_OP]['+'] = op_entered;
	new_calc->table[WAIT_FOR_OP]['-'] = op_entered;
	new_calc->table[WAIT_FOR_OP]['*'] = op_entered;
	new_calc->table[WAIT_FOR_OP]['/'] = op_entered;
	new_calc->table[WAIT_FOR_OP]['^'] = op_entered;
	new_calc->table[WAIT_FOR_OP][')'] = close_par_entered;
	new_calc->table[WAIT_FOR_OP]['\0'] = end_entered;
}

void CalculatorDestroy(calc_t *calc)
{
	assert(calc);

	StackDestroy(calc->num_stack);
	StackDestroy(calc->operators_stack);

	Free(calc);
}

double CalculatorCalculate(const char *str,
						   status_t *out_param_status,
						   calc_t *calc)
{
	state_t next_state = 0;
	state_t current_state = WAIT_FOR_NUM;
	double answer = 0;

	assert(str);
	assert(out_param_status);
	assert(calc);

	*out_param_status = CALCULATOR_SUCCESS;

	/* while the string doesn't reach end and exit status is CALCULATOR_SUCCESS */
	while (StackPeek(calc->operators_stack) != &end &&
		   *out_param_status == CALCULATOR_SUCCESS)
	{
		next_state = calc->table[current_state][(size_t)*str].next_state;
		*out_param_status = calc->table[current_state][(size_t)*str].handler((char **)&str, calc);
		current_state = next_state;
	}

	/* get the answer out of the stack */
	if (*out_param_status == CALCULATOR_SUCCESS)
	{
		answer = *(double *)StackPeek(calc->num_stack);
	}
	else
	{
		answer = 0;
	}

	/* empty the stacks from any left content */
	while (!StackIsEmpty(calc->num_stack))
	{
		Free(StackPeek(calc->num_stack));
		StackPop(calc->num_stack);
	}

	while (!(StackSize(calc->operators_stack) == 1))
	{
		StackPop(calc->operators_stack);
	}

	return (answer);
}

static status_t Add(double *num1, double num2)
{
	assert(num1);

	*num1 += num2;

	return (CALCULATOR_SUCCESS);
}

static status_t Sub(double *num1, double num2)
{
	assert(num1);

	*num1 -= num2;

	return (CALCULATOR_SUCCESS);
}

static status_t Mult(double *num1, double num2)
{
	assert(num1);

	*num1 *= num2;

	return (CALCULATOR_SUCCESS);
}

static status_t Div(double *num1, double num2)
{
	assert(num1);

	if (num2 == 0)
	{
		return (MATH_ERROR);
	}

	*num1 /= num2;

	return (CALCULATOR_SUCCESS);
}

static status_t Pow(double *num1, double num2)
{
	int i = 0;
	double result = 1;
	
	if (num2 < 0)
	{
		*num1 = 1 / *num1;
		num2 *= (-1);
	}
	
	while (i != num2)
	{
		result *= *num1;
		++i;
	}
	
	*num1 = result;
	return (CALCULATOR_SUCCESS);
}

static status_t SyntaxErrorFunc(double *num1, double num2)
{
	(void)num1;
	(void)num2;

	return (SYNTAX_ERROR);
}

static status_t EmptyFunc(double *num1, double num2)
{
	(void)num1;
	(void)num2;

	return (CALCULATOR_SUCCESS);
}

static status_t ErrorHandler(char **char_ptr, calc_t *calc)
{
	(void)char_ptr;
	(void)calc;

	return (SYNTAX_ERROR);
}

static status_t NumHandler(char **char_ptr, calc_t *calc)
{
	/* make new entry for the num stack */
	double *new_num = (double *)malloc(sizeof(double));

	assert(char_ptr);
	assert(calc);

	if (new_num == NULL)
	{
		return (SYNTAX_ERROR);
	}

	*new_num = strtod(*char_ptr, NULL);
	StackPush(calc->num_stack, new_num);

	++*char_ptr;

	return (CALCULATOR_SUCCESS);
}

static status_t OperatorHandler(char **char_ptr, calc_t *calc)
{
	status_t status = CALCULATOR_SUCCESS;
	double *num1 = NULL;
	double *num2 = NULL;
	operator_t *last_operator = NULL;

	assert(char_ptr);
	assert(calc);

	last_operator = (operator_t *)StackPeek(calc->operators_stack);

	/* while current operator's priority equal or less than the last one */
	while (calc->operators[(int)**char_ptr].priority <=
			   last_operator->priority &&
		   status == CALCULATOR_SUCCESS)
	{
		/* get the last num */
		num2 = (double *)StackPeek(calc->num_stack);
		StackPop(calc->num_stack);

		/* get the one before the last */
		num1 = (double *)StackPeek(calc->num_stack);

		/* call calc_func for the numbers */
		status = last_operator->calc_func(num1, *num2);

		/* pop the operation that just done */
		StackPop(calc->operators_stack);

		Free(num2);

		last_operator = (operator_t *)StackPeek(calc->operators_stack);
	}

	/* push current operation to stack */
	StackPush(calc->operators_stack, &(calc->operators[(int)**char_ptr]));

	/* increment the string in one character */
	++*char_ptr;

	return (status);
}

static status_t CloseParHandler(char **char_ptr, calc_t *calc)
{
	status_t status = CALCULATOR_SUCCESS;
	double *num1 = NULL;
	double *num2 = NULL;
	operator_t *last_operator = NULL;

	assert(char_ptr);
	assert(calc);

	last_operator = (operator_t *)StackPeek(calc->operators_stack);


		/* while we don't get into open parantheses */
		while (status == CALCULATOR_SUCCESS &&
			   !(last_operator->priority == OPEN_PAR))
		{
			/* get the last num */
			num2 = (double *)StackPeek(calc->num_stack);
			StackPop(calc->num_stack);

			/* get the one before the last */
			num1 = (double *)StackPeek(calc->num_stack);

			/* call calc_func for the numbers */
			status = last_operator->calc_func(num1, *num2);

			/* pop only if CALCULATOR_SUCCESS - if not, may be the dummy */
			if (status == CALCULATOR_SUCCESS)
			{
				StackPop(calc->operators_stack);
			}

			Free(num2);
			
			last_operator = (operator_t *)StackPeek(calc->operators_stack);
		}

		/* pop only if CALCULATOR_SUCCESS - if not, may be the dummy */
		if (status == CALCULATOR_SUCCESS)
		{
			StackPop(calc->operators_stack);
		}
	
	/* increment the string in one character */
	++*char_ptr;

	return (status);
}

static status_t OpenParHandler(char **char_ptr, calc_t *calc)
{
	status_t status = CALCULATOR_SUCCESS;

		StackPush(calc->operators_stack, &(calc->operators[(int)**char_ptr]));

	/* increment the string in one character */
	++*char_ptr;

	return (status);
}
static status_t EndHandler(char **char_ptr, calc_t *calc)
{
	status_t status = CALCULATOR_SUCCESS;
	double *num1 = NULL;
	double *num2 = NULL;
	operator_t *last_operator = NULL;

	assert(char_ptr);
	assert(calc);

	(void)char_ptr;

	/* while status is CALCULATOR_SUCCESS and the num stack has anything but the answer */
	while (status == CALCULATOR_SUCCESS &&
		   StackSize(calc->num_stack) != 1)
	{
		last_operator = (operator_t *)StackPeek(calc->operators_stack);

		/* get the last num */
		num2 = (double *)StackPeek(calc->num_stack);
		StackPop(calc->num_stack);

		/* get the one before the last */
		num1 = (double *)StackPeek(calc->num_stack);

		/* call calc_func for the numbers */
		status = last_operator->calc_func(num1, *num2);

		StackPop(calc->operators_stack);

		Free(num2);
	}

	/* push end operator so calculator function will know we reached the end */
	StackPush(calc->operators_stack, (void *)&end);

	return (status);
}
