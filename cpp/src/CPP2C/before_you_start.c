/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdlib.h> /* malloc(), free(), abs(), size_t */
#include <stdio.h>  /* printf(), size_t */

/*#include "utility.h"*/
/********************************* CPP: ***************************************/
/*
class X:
{
public:
    explicit X(int num = 0);

private:
    int m_num;
}

X::X(int num) : m_num(num)
{
}

int main()
{

    X x1;
    X x2(x1);

    return 0;
}
*/

/********************************** C: ****************************************/

typedef struct X
{
    int num;
} x_s;

void x_constructor(x_s *x, int num_)
{
    if (num_ != 0)
    {
        x->num = num_;
    }
    else
    {
        num_ = 0;
    }
}

void x_cctor(x_s *original, x_s *copy)
{
    copy->num = original->num;
}

void x_destructor(x_s *x)
{
    free(x);
}

int main()
{
    x_s *x1 = (x_s *)malloc(sizeof(x_s));
    x_s *x2 = (x_s *)malloc(sizeof(x_s));

    x_constructor(x1, 5);
    x_cctor(x1, x2);

    x_destructor(x1);
    x_destructor(x2);

    return (0);
}
