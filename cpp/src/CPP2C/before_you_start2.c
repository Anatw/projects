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

class Y
{
public:
    virtual ~Y(){}
    virtual void Foo();
    void Bar()const;
private:
    X m_x;
    int m_a;

    Y& operator=(const Y&);
};

class Der: public Y
{
public:
    virtual void Dodo();

private:
    X m_x2;
};



int main() {

    Y y1;
    Der d1;
}

*/

/********************************** C: ****************************************/

/********************************** class x: **********************************/
typedef struct x
{
    int num;
} X;

void x_constructor(X *x, int num_)
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

void x_cctor(X *original, X *copy)
{
    copy->num = original->num;
}

void x_destructor(X *x)
{
    free(x);
}

/********************************** class y: **********************************/

void Foo(Y *y);
void Bar(Y *y);

typedef struct y;

typedef struct vTable_Y
{
    void (*y_destructor)(Y *y);
    void (*Foo)(Y *y);
} VTable_Y;

typedef struct y
{
    VTable_Y *v_ptr;

    X m_x;
    int num;
} Y;

VTable_Y Vtable_of_y = {y_destructor, Foo};

void y_constructor(X *x, int num_x, Y *p_this, int num_y)
{
    p_this->m_x = x;
    x_constructor(x, num_x);
    p_this->num = num_y;
    p_this->v_ptr = &Vtable_of_y;
}

void y_cctor(Y *original, Y *copy)
{
    copy->num = original->num;
}

void y_destructor(Y *y)
{
    free(y);
}

/********************************* class Der: *********************************/
void Dodo();
typedef struct der;

typedef struct vTable_der
{
    void (*Dodo)();
} VTable_DER;

typedef struct der
{
    VTable_DER *v_ptr;

    Y y_der; // inheritance from class y */
    X m_x2;
} Der;

VTable_DER VTable_of_der = {Dodo};

void Der_constructor(X *x, int m_x2_num, Y *y, int num_y, Der *p_this)
{
    y_constructor(&x, m_x2_num, &y, num_y);
    p_this->v_ptr = &VTable_of_der;
}

void Der_cctor(Y *original, Y *copy)
{
    copy->num = original->num;
}

void Der_destructor(Y *y)
{
    free(y);
}

/*********************************** main: ************************************/
int main()
{
    /* Creating members for class y: */
    X *x1 = (X *)malloc(sizeof(X));
    Y *y1 = (Y *)malloc(sizeof(Y));

    /* Constructing class y: */
    //x_constructor(&x1, 5);
    y_constructor(&x1, 5, &y1, 6);

    /* Creating members for class der: */
    X *x_der = (X *)malloc(sizeof(X));
    Y *y_der = (Y *)malloc(sizeof(Y));
    Der *der = (Der *)malloc(sizeof(Der));

    /* Constructing class der: */
    //x_constructor(&x_der, 7);
    der_constructor(&x_der, 7, &y_der, 8, der, );

    /* Destructors: */
    /* Destructing class y: */
    x_destructor(&x1);
    y1->v_ptr->y_destructor(&y1);

    return (0);
}
