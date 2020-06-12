/*******************************************************************************
Functions that start with:
V_ = virtual functions.
S_ = static functions.
PD_ = protected.
PE_ = private.

for variables:
G_ = global.

                            Simple Watchdog
                          Written by Anat Wax
                            May th, 2020
                          Reviewer: 
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */

int G_s_count = 0;

typedef enum tag_ElementType
{
    PublicTransport,
    Minibus,
    Taxi,
    SpecialTaxi
} ElementType;

typedef struct PublicTransport;

typedef struct vTable_PT
{
    void (*V_Destructor)(PublicTransport *p_this);
    void (*V_Display)(PublicTransport *p_this);
} VTable;

typedef struct publicTransport
{
    VTable *v_ptr;
    ElementType PublicTransport;

    void (*PTConstructor)(PublicTransport *p_this);
    void (*PTCCtor)(PublicTransport *p_this, PublicTransport *copy);
    void (*S_PTPrintCount)(PublicTransport *p_this);
    // accessible the this class and derived classes:
    int (*PD_PTGetID)(PublicTransport *p_this);

    int s_count;
    int m_liscence_plate;

} PublicTransport;

void V_PTDestructor(PublicTransport *p_this)
{
}

void V_PTDisplay(PublicTransport *p_this)
{
}

VTable g_VTable_PT = {V_PTDestructor, V_PTDisplay};

typedef struct minibus
{
    ElementType Minibus;

    PublicTransport *p_public_transport;
    p_public_transport->PublicTransport = Minibus;

    void (*MinibusConstructor)(Minibus *p_this);
    void (*MinibusCCtor)(Minibus *p_this, Minibus *copy);
    void (*MinibusDestructor)(Minibus *p_this);
    void (*MinibusDisplay)(Minibus *p_this);
    void (*V_MinibusWash)(Minibus *p_this, int minutes);

    int m_numSeates;
} Minibus;

void V_MinibusDestructor(PublicTransport *p_this)
{
}

void V_MinibusDisplay(PublicTransport *p_this)
{
}

VTable g_VTable_Minibus = {V_MinibusDestructor, V_MinibusDisplay};

typedef struct taxi
{
    ElementType Taxi;

    PublicTransport *p_public_transport;

    void (*TaxiConstructor)(Taxi *p_this);
    void (*TaxiCCtor)(Taxi *p_this, Taxi *copy);
    void (*TaxiDestructor)(Taxi *p_this);
    void (*TaxiDisplay)(Taxi *p_this);
} Taxi;

int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

void V_TaxiDestructor(PublicTransport *p_this)
{
}

void V_TaxiDisplay(PublicTransport *p_this)
{
}

VTable g_VTable_Minibus = {V_TaxiDestructor, V_TaxiDisplay};

typedef struct specialTaxi
{
    ElementType *SpecialTaxi;

    Taxi *p_taxi;

    void (*SpecialTConstructor)(SpecialTaxi *p_this);
    void (*SpecialTCCtor)(SpecialTaxi *p_this, SpecialTaxi *copy);
    void (*SpecialTDestructor)(SpecialTaxi *p_this);
    void (*SpecialTDisplay)(SpecialTaxi *p_this);

} SpecialTaxi;

void V_SpecialTDestructor(PublicTransport *p_this)
{
}

void V_SpecialTDisplay(PublicTransport *p_this)
{
}

VTable g_VTable_Minibus = {V_SpecialTDestructor, V_SpecialTDisplay};

void PTPrintInfo(PublicTransport *p_this)
{
    if (p_this->PublicTransport)
    {
    }
    else
    {
        if (p_this->publicTransport->Minibus)
        {
        }
        else if (p_this->Taxi)
    }

    {
    }
    else if (p_this->SpecialTaxi)
    {
    }
}

int main()
{

    return (0);
}
