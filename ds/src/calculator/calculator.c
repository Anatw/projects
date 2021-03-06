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
#include <stdlib.h> /* calloc(), free(), size_t, fabs() */
#include <string.h> /* size_t, atoi() */
#include <stdio.h>  /* printf() */

#include "calculator.h"
#include "stack.h"

#define ASCII_RANGE (256)
#define FREE(x) ((free(x), (x = NULL)))
#define RETURN_ERR (0)
#define UNUSED(y) ((void)(y))

typedef enum
{
    WAIT_FOR_NUM = 0,
    WAIT_FOR_OP = 1,
    ERROR = 2,
    MEMORY_ERROR,
    STATE_RANGE
} state_t;

typedef enum
{
    NOTHING = 0,
    CLOSING_PAR,
    SUB,
    ADD = SUB,
    MULT,
    DIV = MULT,
    POW,
    OPEN_PAR
} operation_priority_t;

typedef struct
{
    /* We use char** and not char* in order for the handler to increment 
    the runner char* pointer. */
    void (*handler)(const char **char_ptr, status_t *status, calc_t *calc);
    state_t next_state;
} state_entry_t;

typedef struct
{
    /* double* num1 may be just double if more convenient for you*/
    status_t (*calc_func)(double *num1, double num2);
    operation_priority_t priority;
} operator_t;

struct calculator
{
    state_entry_t table[STATE_RANGE][ASCII_RANGE];
    operator_t operators[ASCII_RANGE];
    stack_t *num_stack;
    stack_t *op_stack;
};

/************************* opertaion functions: *******************************/

static status_t calcAdd(double *num1, double num2);
static status_t calcSubtract(double *num1, double num2);
static status_t calcMultiply(double *num1, double num2);
static status_t calcDevide(double *num1, double num2);
static status_t calcPower(double *num1, double num2);

static void EmptyStacks(calc_t *calc);
static double ClosingHandler(state_t state, status_t *out_param_status,
                             calc_t *calc);

static void OperationHandler(const char **character, status_t *status,
                             calc_t *calc);
static void ClosingBrackets(const char **character, status_t *status,
                            calc_t *calc);
static void OpeningBrackets(const char **brackets, status_t *status,
                            calc_t *calc);
static void NumHandler(const char **digit, status_t *status, calc_t *calc);
static void calcCreateOperators(operator_t operators[ASCII_RANGE]);
static void calcCreateTable(state_entry_t table[][ASCII_RANGE]);
static double calcMainHandler(const char *str, status_t *out_param_status,
                              calc_t *calc);


/******************************************************************************/
/************************* fundamental functions: *****************************/
/******************************************************************************/

calc_t *CalculatorInit(size_t max_length)
{
    calc_t *calc = NULL;
    stack_t *num_stack = NULL;
    stack_t *op_stack = NULL;

    calc = (calc_t *)calloc(1, sizeof(calc_t));
    if (!calc)
    {
        return (NULL);
    }
    num_stack = StackCreate(max_length);
    if (!num_stack)
    {
        FREE(calc);
        return (NULL);
    }

    op_stack = StackCreate(max_length);
    if (!op_stack)
    {
        FREE(calc);
        FREE(num_stack);
        return (NULL);
    }

    calcCreateTable(calc->table);
    calcCreateOperators(calc->operators);
    calc->num_stack = num_stack;
    calc->op_stack = op_stack;

    return (calc);
}

/******************************************************************************/

void CalculatorDestroy(calc_t *calc)
{
    StackDestroy(calc->num_stack);
    StackDestroy(calc->op_stack);

    FREE(calc);
}

/******************************************************************************/

double CalculatorCalculate(const char *str, status_t *out_param_status,
                           calc_t *calc)
{
    double result = 0;
    result = calcMainHandler(str, out_param_status, calc);

    if (*out_param_status != SUCCESS)
    {
        MATH_ERROR == *out_param_status ? printf("MATH_ERROR\n") :
                                          printf("SYNTAX_ERROR\n");
        EmptyStacks(calc);
        return (RETURN_ERR);
    }

    return (result);
}

/******************************************************************************/
/*************************** utility functions: *******************************/
/******************************************************************************/

static double calcMainHandler(const char *str, status_t *out_param_status,
                              calc_t *calc)
{
    state_t state = WAIT_FOR_NUM;
    *out_param_status = SUCCESS;

    while (*str != '\0')
    {
        /* this part is calling the function 'OperationHandler': */
        calc->table[state][(unsigned char)*str].handler(&str, out_param_status,
                                                        calc);

        if (SUCCESS != *out_param_status)
        {
            return (RETURN_ERR);
        }

        state = calc->table[state][(unsigned char)*str].next_state;
        ++str;
    }

    if (WAIT_FOR_NUM == state) 
    {
        *out_param_status = SYNTAX_ERROR;
        return (RETURN_ERR);
    }
    /* if ('\0' == *str): */
    return (ClosingHandler(state, out_param_status, calc));
}

/************************* utility functions: *********************************/

static void SyntaxErrorHandler(const char **character, status_t *status,
                               calc_t *calc)
{
    UNUSED(character);
    UNUSED(calc);
    *status = SYNTAX_ERROR;
}

/******************************************************************************/

static status_t CalcErrorHandler(double *num1, double num2)
{
    UNUSED(num1);
    UNUSED(num2);
    return (SYNTAX_ERROR);
}

/******************************************************************************/

static void calcCreateTable(state_entry_t table[][ASCII_RANGE])
{
    int i = 0;
    int j = 0;

    /* initialize all lut element to error: */
    for (i = 0; i < STATE_RANGE; ++i)
    {
        for (j = 0; j < ASCII_RANGE; ++j)
        {
            table[i][j].handler = SyntaxErrorHandler;
            table[i][j].next_state = ERROR;
        }
    }

    /* setting operators inside the table: */
    table[0]['('].handler = OpeningBrackets;
    table[0]['('].next_state = WAIT_FOR_NUM;

    table[1][')'].handler = ClosingBrackets;
    table[1][')'].next_state = WAIT_FOR_OP;

    table[1]['+'].handler = OperationHandler;
    table[1]['+'].next_state = WAIT_FOR_NUM;

    table[1]['-'].handler = OperationHandler;
    table[1]['-'].next_state = WAIT_FOR_NUM;

    table[1]['*'].handler = OperationHandler;
    table[1]['*'].next_state = WAIT_FOR_NUM;

    table[1]['/'].handler = OperationHandler;
    table[1]['/'].next_state = WAIT_FOR_NUM;

    table[1]['^'].handler = OperationHandler;
    table[1]['^'].next_state = WAIT_FOR_NUM;

    /* setting numbers inside the table: */
    table[0]['0'].handler = NumHandler;
    table[0]['0'].next_state = WAIT_FOR_OP;

    table[0]['1'].handler = NumHandler;
    table[0]['1'].next_state = WAIT_FOR_OP;

    table[0]['2'].handler = NumHandler;
    table[0]['2'].next_state = WAIT_FOR_OP;

    table[0]['3'].handler = NumHandler;
    table[0]['3'].next_state = WAIT_FOR_OP;

    table[0]['4'].handler = NumHandler;
    table[0]['4'].next_state = WAIT_FOR_OP;

    table[0]['5'].handler = NumHandler;
    table[0]['5'].next_state = WAIT_FOR_OP;

    table[0]['6'].handler = NumHandler;
    table[0]['6'].next_state = WAIT_FOR_OP;

    table[0]['7'].handler = NumHandler;
    table[0]['7'].next_state = WAIT_FOR_OP;

    table[0]['8'].handler = NumHandler;
    table[0]['8'].next_state = WAIT_FOR_OP;

    table[0]['9'].handler = NumHandler;
    table[0]['9'].next_state = WAIT_FOR_OP;
}

/******************************************************************************/

static void calcCreateOperators(operator_t operators[ASCII_RANGE])
{
    int i = 0;

    for (i = 0; i < STATE_RANGE; ++i)
    {
        operators[i].calc_func = CalcErrorHandler;
        operators[i].priority = NOTHING;
    }

    operators['+'].calc_func = calcAdd;
    operators['+'].priority = ADD;

    operators['-'].calc_func = calcSubtract;
    operators['-'].priority = SUB;

    operators['*'].calc_func = calcMultiply;
    operators['*'].priority = MULT;

    operators['/'].calc_func = calcDevide;
    operators['/'].priority = DIV;

    operators['^'].calc_func = calcPower;
    operators['^'].priority = POW;
}

/******************************************************************************/

static status_t calcAdd(double *num1, double num2)
{
    *num1 += num2;

    return (SUCCESS);
}

/******************************************************************************/

static status_t calcSubtract(double *num1, double num2)
{
    *num1 -= num2;

    return (SUCCESS);
}

/******************************************************************************/

static status_t calcMultiply(double *num1, double num2)
{
    *num1 *= num2;

    return (SUCCESS);
}

/******************************************************************************/

static status_t calcDevide(double *num1, double num2)
{
    if (0 == num2)
    {
        *num1 = RETURN_ERR;
        return (MATH_ERROR);
    }

    *num1 /= num2;

    return (SUCCESS);
}

/******************************************************************************/

static status_t calcPower(double *num1, double num2)
{
    int i = 0;
    double num = 1;
    int is_negative = 0;

    if (0 > num2 && 0 == *num1)
    {
        *num1 = RETURN_ERR;
        return (MATH_ERROR);
    }

    if (num2 < 0)
    {
        num2 *= -1;
        is_negative = 1;
    }

    for (i = 0; i < num2; ++i)
    {
        num *= *num1;
    }

    *num1 = is_negative ? 1 / num : num;

    return (SUCCESS);
}

/******************************************************************************/

static void NumHandler(const char **digit, status_t *status, calc_t *calc)
{
    double *number = (double *)calloc(1, sizeof(double));
    if (NULL == number)
    {
        *status = MEMORY_ERROR;
    }

    *number = strtod(*digit, NULL);

    StackPush(number, calc->num_stack);
    *status = SUCCESS;
}

/******************************************************************************/

static void OpeningBrackets(const char **brackets, status_t *status,
                            calc_t *calc)
{
    *status = SUCCESS;
    StackPush(*(char **)brackets, calc->op_stack);
}

/******************************************************************************/

static void ClosingBrackets(const char **character, status_t *status,
                            calc_t *calc)
{
    double num2 = 0;
    unsigned char oper = 0;
    char opening_brackets = '(';
    UNUSED(character);

    while (opening_brackets != *((char *)StackPeek(calc->op_stack)))
    {
        oper = *((unsigned char *)StackPeek(calc->op_stack));
        num2 = *((double *)StackPeek(calc->num_stack));
        free(StackPeek(calc->num_stack));
        StackPop(calc->num_stack);

        *status = calc->operators[oper].calc_func(StackPeek(calc->num_stack),
                                                  num2);

        StackPop(calc->op_stack);

        /* if string has only ')' with no '(': */
        if (StackIsEmpty(calc->op_stack))
        {
            *status = SYNTAX_ERROR;
            return;
        }
    }

    /* pop the opening brackets: */
    StackPop(calc->op_stack);
}

/******************************************************************************/

static void OperationHandler(const char **character, status_t *status,
                             calc_t *calc)
{
    unsigned char operation = 0;
    double *number2 = 0;
    *status = SUCCESS;

    if (StackIsEmpty(calc->op_stack))
    {
        StackPush(*(char **)character, calc->op_stack);

        return;
    }

    operation = *((char *)StackPeek(calc->op_stack));

    /* if the new operator (character) is smaller or equal to the */
    /* top operator inside the stack (operator): */
    if (calc->operators[operation].priority >=
        calc->operators[(unsigned char)**character].priority)
    {
        while (!StackIsEmpty(calc->op_stack))
        {
            if ((calc->operators[operation].priority >=
                 calc->operators[(unsigned char)**character].priority) &&
                ('(' != *((char *)StackPeek(calc->op_stack))))
            {
                operation = *((char *)StackPeek(calc->op_stack));
                number2 = ((double *)StackPeek(calc->num_stack));
                StackPop(calc->num_stack);

                calc->operators[operation].calc_func(StackPeek(calc->num_stack),
                                                               *number2);
                /* pop old operation sign and push the new one */
                StackPop(calc->op_stack);

                free(number2);
                number2 = NULL;
            }
        }
    }

    StackPush(*(char **)character, calc->op_stack);
}

/******************************************************************************/

static double ClosingHandler(state_t state, status_t *out_param_status,
                             calc_t *calc)
{
    double result = 0;
    unsigned char oper = 0;
    /* if the string ends with mathematic operation: */
    if (1 != state)
    {
        *out_param_status = SYNTAX_ERROR;
        return (RETURN_ERR);
    }

    while (!StackIsEmpty(calc->op_stack))
    {
        oper = *((char *)StackPeek(calc->op_stack));
        result = *((double *)StackPeek(calc->num_stack));
        free(StackPeek(calc->num_stack));
        StackPop(calc->num_stack);

        *out_param_status = calc->operators[oper].
                            calc_func(StackPeek(calc->num_stack), result);
        StackPop(calc->op_stack);

       /* if (SUCCESS != *out_param_status)
        {
            return (RETURN_ERR);
        }*/
    }

    result = *((double *)StackPeek(calc->num_stack));
    free(StackPeek(calc->num_stack));
    StackPop(calc->num_stack);

    return (result);
}

/******************************************************************************/

static void EmptyStacks(calc_t *calc)
{
    while (!StackIsEmpty(calc->num_stack))
    {
        free(StackPeek(calc->num_stack));
        StackPop(calc->num_stack);
    }

    while (!StackIsEmpty(calc->op_stack))
    {
        StackPop(calc->op_stack);
    }
}