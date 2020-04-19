#include <stdlib.h> /* malloc(), free(), size_t, abs() */
#include <string.h> /* size_t, atoi() */

#include "calculator.h"
#include "stack.h"

#define ASCII_RANGE (256)
#define FREE(x) ((free(x), (x = NULL)))

typedef enum
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	ERROR =  2,
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
}operation_priority_t;

typedef struct 
{
	/* We use char** and not char* in order for the handler to increment the runner
    char* pointer. */
	status_t (*handler)(char **char_ptr, calc_t *calc);
	state_t next_state;
}state_entry_t;

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

/****************************** functions: ************************************/

calc_t *CalculatorInit(size_t max_length)
{
    calc_t *calculator = (calc_t *)malloc(sizeof(calc_t));
    stack_t *num_stack = NULL;
    stack_t *op_stack = NULL;
    /* STATE_RANGE is defined at state_t: */
    state_entry_t table[STATE_RANGE][ASCII_RANGE] = {0};
    operator_t operators[ASCII_RANGE] = {0};

    num_stack = StackCreate(max_length);
    if (!num_stack)
    {
        return (NULL);
    }
    
    op_stack = StackCreate(max_length);
    if (!op_stack)
    {
        FREE(num_stack);
        return (NULL);
    }
    
    StackPush(num_stack, NOTHING);

    calculator->table = CalculatorCreateTtable(calculator);
    calculator->operators = CalculatorCreateOperators();
    calculator->num_stack = num_stack;
    calculator->op_stack = op_stack;

    return (calculator);
}

void CalculatorDestroy(calc_t *calc)
{
    StackDestroy(calc->num_stack);
    StackDestroy(calc->op_stack);

    FREE(calc);
}
/*
double CalculatorCalculate(const char *str, status_t *out_param_status,
                           calc_t *calc)
{
    
    int number = atoi(str, strlen(str), 0, 10);
        
    while ('\0' != str)
}*/



state_entry_t CalculatorCreateTable(calc_t *calc)
{
    state_entry_t table[STATE_RANGE][ASCII_RANGE] = {0};
    int i = 0;
    int j = 0;

    /* initialize all lut element to error: */
    for (i = 0; i < STATE_RANGE; ++i)
    {
        for (j = 0; j < ASCII_RANGE; ++j)
        {
            table[i][j].handler = SYNTAX_ERROR;
            table[i][j].next_state = ERROR;
        }
    }

    /* setting operators inside the table: */
    table[0]['('].handler = SUCCESS;
    table[0]['('].next_state = WAIT_FOR_NUM;

    table[1][')'].handler = SUCCESS;
    table[1][')'].next_state = WAIT_FOR_OP;

    table[1]['+'].handler = CalculatorAdd;
    table[1]['+'].next_state = WAIT_FOR_NUM;

    table[1]['-'].handler = CalculatorSubtract;
    table[1]['-'].next_state = WAIT_FOR_NUM;
    
    table[1]['*'].handler = CalculatorDouble;
    table[1]['*'].next_state = WAIT_FOR_NUM;

    table[1]['/'].handler = CalculatorDevide;
    table[1]['/'].next_state = WAIT_FOR_NUM;

    table[1]['^'].handler = CalculatorPower;
    table[1]['^'].next_state = WAIT_FOR_NUM;

    /* setting numbers inside the table: */
    table[0]['0'].handler = NumHandler(calculator, *(char *)table[0]['0']);
    table[0]['0'].next_state = WAIT_FOR_OP;

    table[0]['1'].handler = NumHandler(calculator, *(char *)table[0]['1']);
    table[0]['1'].next_state = WAIT_FOR_OP;

    table[0]['2'].handler = NumHandler(calculator, *(char *)table[0]['2']);
    table[0]['2'].next_state = WAIT_FOR_OP;

    table[0]['3'].handler = NumHandler(calculator, *(char *)table[0]['3']);
    table[0]['3'].next_state = WAIT_FOR_OP;

    table[0]['4'].handler = NumHandler(calculator, *(char *)table[0]['4']);
    table[0]['4'].next_state = WAIT_FOR_OP;

    table[0]['5'].handler = NumHandler(calculator, *(char *)table[0]['5']);
    table[0]['5'].next_state = WAIT_FOR_OP;

    table[0]['6'].handler = NumHandler(calculator, *(char *)table[0]['6']);
    table[0]['6'].next_state = WAIT_FOR_OP;

    table[0]['7'].handler = NumHandler(calculator, *(char *)table[0]['7']);
    table[0]['7'].next_state = WAIT_FOR_OP;

    table[0]['8'].handler = NumHandler(calculator, *(char *)table[0]['8']);
    table[0]['8'].next_state = WAIT_FOR_OP;

    table[0]['9'].handler = NumHandler(calculator, *(char *)table[0]['9']);
    table[0]['9'].next_state = WAIT_FOR_OP;

    return (table);
}

operator_t CalculatorCreateOperators()
{
    operator_t operators[ASCII_RANGE] = {0};
    int i = 0;

    for (i = 0; i < STATE_RANGE; ++i)
    {
        operators[i].calc_func = SYNTAX_ERROR;
        operators[i].priority = ERROR;
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

    return (operators);
}

static status_t CalculatorAdd(double *num1, double num2)
{
    num1 += num2;

    return (SUCCESS);
}

static status_t CalculatorSubtract(double *num1, double num2)
{
    num1 -= num2;

    return (SUCCESS);
}

static status_t CalculatorMultiply(double *num1, double num2)
{
    num1 *= num2;

    return (SUCCESS);
}

static status_t CalculatorDevide(double *num1, double num2)
{
    num1 /= num2;

    return (SUCCESS);
}

static status_t CalculatorPower(double *num1, double num2)
{
    int index = 0;

    if (0 == num2)
    {
        return (SYNTAX_ERROR);
    }

    if (num2 < 0)
    {
        num2 = abs(num2);
        while (num2 != 0)
        {
            *num1 = 1 / *num1;
            --num2;
        }

        return (SUCCESS);
    }

    while (index = 0; index < num2; ++index)
    {
        *num1 *= *num1;
    }

    return (SUCCESS);
}

PushToStack(calc_t * calculator, char *digit)
{
    StackPush(digit, calculator->num_stack);
}