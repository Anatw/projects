#include <stdlib.h> /* malloc(), free(), size_t, abs() */
#include <string.h> /* size_t, atoi() */
#include <stdio.h>  /* printf() */
#include <math.h>

#include "calculator.h"
#include "stack.h"

#define ASCII_RANGE (256)
#define FREE(x) ((free(x), (x = NULL)))
#define RETURN_ERR (1010101010101)
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
    /* We use char** and not char* in order for the handler to increment the runner
    char* pointer. */
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

static status_t CalculatorAdd(double *num1, double num2);
static status_t CalculatorSubtract(double *num1, double num2);
static status_t CalculatorMultiply(double *num1, double num2);
static status_t CalculatorDevide(double *num1, double num2);
static status_t CalculatorPower(double *num1, double num2);

static void EmptyStacks(calc_t *calculator);
static double ClosingHandler(state_t state, status_t *out_param_status,
                             calc_t *calculator);

static void OperationHandler(const char **character, status_t *status, calc_t *calculator);
static void ClosingBrackets(const char **character, status_t *status, calc_t *calculator);
static void OpeningBrackets(const char **brackets, status_t *status, calc_t *calculator);
static void NumHandler(const char **digit, status_t *status, calc_t *calculator);
static void CalculatorCreateOperators(operator_t operators[ASCII_RANGE]);
static void CalculatorCreateTable(state_entry_t table[][ASCII_RANGE]);
static double CalculatorMainHandler(const char *str, status_t *out_param_status,
                                    calc_t *calc);

/****************************** functions: ************************************/

calc_t *CalculatorInit(size_t max_length)
{
    calc_t *calculator = NULL;
    stack_t *num_stack = NULL;
    stack_t *op_stack = NULL;

    calculator = (calc_t *)malloc(sizeof(calc_t));
    if (!calculator)
    {
        return (NULL);
    }
    num_stack = StackCreate(max_length);
    if (!num_stack)
    {
        FREE(calculator);
        return (NULL);
    }

    op_stack = StackCreate(max_length);
    if (!op_stack)
    {
        FREE(calculator);
        FREE(num_stack);
        return (NULL);
    }

    CalculatorCreateTable(calculator->table);
    CalculatorCreateOperators(calculator->operators);
    calculator->num_stack = num_stack;
    calculator->op_stack = op_stack;

    return (calculator);
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
    result = CalculatorMainHandler(str, out_param_status, calc);

    if (*out_param_status != SUCCESS)
    {
        MATH_ERROR == *out_param_status ? printf("MATH_ERROR\n") : printf("SYNTAX_ERROR\n");
        EmptyStacks(calc);
        return (RETURN_ERR);
    }

    return (result);
}

static double CalculatorMainHandler(const char *str, status_t *out_param_status,
                                    calc_t *calc)
{
    state_t state = WAIT_FOR_NUM;
    *out_param_status = SUCCESS;

    while (*str != '\0')
    {
        /* this part is calling the function 'OperationHandler': */
        calc->table[state][(unsigned char)*str].handler(&str, out_param_status, calc);

        if (SUCCESS != *out_param_status)
        {
            return (RETURN_ERR);
        }

        state = calc->table[state][(unsigned char)*str].next_state;
        ++str;
    }

    /* if ('\0' == *str): */
    return (ClosingHandler(state, out_param_status, calc));
}

/************************* utility functions: *********************************/

static void SyntaxErrorHandler(const char **character, status_t *status, calc_t *calculator)
{
    UNUSED(character);
    UNUSED(calculator);
    *status = SYNTAX_ERROR;
}

static status_t CalcErrorHandler(double *num1, double num2)
{
    UNUSED(num1);
    UNUSED(num2);
    return (SYNTAX_ERROR);
}

static void CalculatorCreateTable(state_entry_t table[][ASCII_RANGE])
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

static void CalculatorCreateOperators(operator_t operators[ASCII_RANGE])
{
    int i = 0;

    for (i = 0; i < STATE_RANGE; ++i)
    {
        operators[i].calc_func = CalcErrorHandler;
        operators[i].priority = NOTHING;
    }

    operators['+'].calc_func = CalculatorAdd;
    operators['+'].priority = ADD;

    operators['-'].calc_func = CalculatorSubtract;
    operators['-'].priority = SUB;

    operators['*'].calc_func = CalculatorMultiply;
    operators['*'].priority = MULT;

    operators['/'].calc_func = CalculatorDevide;
    operators['/'].priority = DIV;

    operators['^'].calc_func = CalculatorPower;
    operators['^'].priority = POW;
}

static status_t CalculatorAdd(double *num1, double num2)
{
    *num1 += num2;

    return (SUCCESS);
}

static status_t CalculatorSubtract(double *num1, double num2)
{
    *num1 -= num2;

    return (SUCCESS);
}

static status_t CalculatorMultiply(double *num1, double num2)
{
    *num1 *= num2;

    return (SUCCESS);
}

static status_t CalculatorDevide(double *num1, double num2)
{
    if (0 == num2)
    {
        return (SYNTAX_ERROR);
    }

    *num1 /= num2;

    return (SUCCESS);
}

static status_t CalculatorPower(double *num1, double num2)
{
    int index = 0;

    if (0 == num2)
    {
        return (1);
    }
    /* number in negative power is a mathematical error: */
    else if (0 == *num1 && 0 < num2)
    {
        return (SYNTAX_ERROR);
    }

    if (num2 < 0)
    {
        num2 = fabs(num2);
        while (num2 != 0)
        {
            *num1 = 1 / *num1;
            --num2;
        }

        return (SUCCESS);
    }

    for (index = 0; index < num2; ++index)
    {
        *num1 *= *num1;
    }

    return (SUCCESS);
}

static void NumHandler(const char **digit, status_t *status, calc_t *calculator)
{
    double *number = (double *)malloc(sizeof(double));
    if (NULL == number)
    {
        *status = MEMORY_ERROR;
    }

    *number = strtod(*digit, NULL);

    StackPush(number, calculator->num_stack);
    *status = SUCCESS;
}

static void OpeningBrackets(const char **brackets, status_t *status, calc_t *calculator)
{
    UNUSED(status);
    StackPush(brackets, calculator->op_stack);
}

static void ClosingBrackets(const char **character, status_t *status, calc_t *calculator)
{
    double num2 = 0;
    unsigned char oper = 0;
    char opening_brackets = '(';
    UNUSED(character);

    while (opening_brackets != *((char *)StackPeek(calculator->op_stack)))
    {
        oper = *((unsigned char *)StackPeek(calculator->op_stack));
        num2 = *((double *)StackPeek(calculator->num_stack));
        StackPop(calculator->num_stack);

        calculator->operators[oper].calc_func(StackPeek(calculator->num_stack), num2);

        StackPop(calculator->op_stack);

        /* if string has only ')' with no '(': */
        if (StackIsEmpty(calculator->op_stack))
        {
            *status = SYNTAX_ERROR;
            return;
        }
    }

    /* pop the opening brackets: */
    StackPop(calculator->op_stack);
}

static void OperationHandler(const char **character, status_t *status, calc_t *calculator)
{
    unsigned char operation = 0;
    double number2 = 0;
    *status = SUCCESS;

    if (StackIsEmpty(calculator->op_stack))
    {
        StackPush(*(char **)character, calculator->op_stack);

        return;
    }

    operation = *((char *)StackPeek(calculator->op_stack));

    /* if the new operator (operation) is smaller or equal to the */
    /* top operator inside the stack: */
    if (calculator->operators[operation].priority >=
        calculator->operators[(unsigned char)**character].priority)
    {
        while (!StackIsEmpty(calculator->op_stack))
        {
            if ((calculator->operators[operation].priority >=
                calculator->operators[(unsigned char)**character].priority) ||
                ('(' != *((char *)StackPeek(calculator->op_stack))))
            {
                number2 = *((double *)StackPeek(calculator->num_stack));
                StackPop(calculator->num_stack);

                calculator->operators[operation].calc_func(StackPeek(calculator->num_stack), number2);
                /* pop old operation sign and push the new one */
                StackPop(calculator->op_stack);
            }
        }
    }

    StackPush(character, calculator->op_stack);
}

static double ClosingHandler(state_t state, status_t *out_param_status,
                             calc_t *calculator)
{
    double result = 0;
    unsigned char oper = 0;
    /* if the string ends with mathematic operation: */
    if (1 != state)
    {
        *out_param_status = SYNTAX_ERROR;
        return (RETURN_ERR);
    }

    while (!StackIsEmpty(calculator->op_stack))
    {
        oper = *((char *)StackPeek(calculator->op_stack));
        result = *((double *)StackPeek(calculator->num_stack));
        free(StackPeek(calculator->num_stack));
        StackPop(calculator->num_stack);

        calculator->operators[oper].calc_func(StackPeek(calculator->num_stack), result);
        StackPop(calculator->op_stack);
    }

    result = *((double *)StackPeek(calculator->num_stack));
    StackPop(calculator->num_stack);

    return (result);
}

static void EmptyStacks(calc_t *calculator)
{
    while (!StackIsEmpty(calculator->num_stack))
    {
        StackPop(calculator->num_stack);
    }

    while (!StackIsEmpty(calculator->op_stack))
    {
        StackPop(calculator->num_stack);
    }
}
