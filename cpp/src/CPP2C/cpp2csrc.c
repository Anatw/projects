/*******************************************************************************
This is an implementation in C of a CPP source code.

Functions that start with:
V_ = virtual functions.
S_ = static functions.
PD_ = protected.
PE_ = private.

for variables:
G_ = global.

cpp2csrc
Written by Anat Wax
Created on: June 10th, 2020
Reviewer: Lior Cohen
*******************************************************************************/
#include <stdio.h>  /* printf(), size_t */
#include <string.h> /* size_t, atoi(), memset() */
#include <stdlib.h> /* malloc(), free(), abs(), size_t */

static int s_count = 0;

/*                            PublicTransport:                                */

typedef struct publicTransport PublicTransport;

typedef struct vTable_PT
{
    void (*V_Destructor)(PublicTransport *p_this);
    void (*V_Display)(PublicTransport *p_this);
} VTable;

struct publicTransport
{
    VTable *v_ptr;

    /* int s_count; - this is a global variable in the C version */
    int m_liscence_plate;
};

void V_PTDestructor(PublicTransport *p_this)
{
    p_this->m_liscence_plate = s_count--;
    printf("PublicTransport::Dtor() %d\n", p_this->m_liscence_plate);
}

void V_PTDisplay(PublicTransport *p_this)
{
    printf("PublicTransport::display(): %d\n", p_this->m_liscence_plate);
}

VTable g_VTable_PT = {V_PTDestructor, V_PTDisplay};

void PTConstructor(PublicTransport *p_this)
{
    p_this->v_ptr = &g_VTable_PT;
    p_this->m_liscence_plate = ++s_count;

    printf("PublicTransport::Ctor() %d\n", p_this->m_liscence_plate);
}

void PTCCtor(PublicTransport *p_this, PublicTransport *copy)
{
    /*copy->v_ptr = p_this->v_ptr;
    copy->m_liscence_plate = s_count;*/

    p_this->v_ptr = &g_VTable_PT;
    p_this->m_liscence_plate = ++s_count;

    printf("PublicTransport::CCtor() %d\n", p_this->m_liscence_plate);
}

void S_PTPrintCount()
{
    printf("s_count: %d\n", s_count);
}

int PD_PTGetID(PublicTransport *p_this)
{
    return (p_this->m_liscence_plate);
}

/*****                         Mininbus:                                  *****/

typedef struct minibus
{
    PublicTransport p_public_transport;
    int m_numSeates;
} Minibus;

void V_MinibusDestructor(Minibus *p_this)
{
    printf("Minibus::Dtor()\n");

    V_PTDestructor(&(p_this->p_public_transport));
}

void V_MinibusDisplay(Minibus *p_this)
{
    printf("Minibus::display() ID: %d num seats: %d\n", p_this->p_public_transport.m_liscence_plate, p_this->m_numSeates);
}

void V_MinibusWash(Minibus *p_this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes,
           p_this->p_public_transport.m_liscence_plate);
}

struct Minibus_VTable
{
    VTable mb_vtable;
    void (*Wash)(Minibus *, int min);
};
struct Minibus_VTable g_VTable_Minibus =
    {{(void (*)(PublicTransport *))V_MinibusDestructor,
      (void (*)(PublicTransport *))V_MinibusDisplay},
     V_MinibusWash};

void MinibusConstructor(Minibus *p_this)
{
    PTConstructor(&(p_this->p_public_transport));
    p_this->p_public_transport.v_ptr = (VTable *)&g_VTable_Minibus;
    p_this->m_numSeates = 20;

    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus *p_this, Minibus *copy)
{
    PTCCtor(&(p_this->p_public_transport), &(copy->p_public_transport));
    copy->p_public_transport = p_this->p_public_transport;
    copy->m_numSeates = p_this->m_numSeates;

    printf("Minibus::CCtor()\n");
}

/*****                              Taxi:                                 *****/

struct vtable_taxi
{
    VTable p_vtable;
};

typedef struct taxi
{
    PublicTransport p_public_transport;
} Taxi;

int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

void V_TaxiDestructor(Taxi *p_this)
{
    printf("Taxi::Dtor()\n");

    V_PTDestructor(&(p_this->p_public_transport));
}

void V_TaxiDisplay(Taxi *p_this)
{
    printf("Taxi::display() ID: %d\n",
           p_this->p_public_transport.m_liscence_plate);
}

struct vtable_taxi g_VTable_Taxi =
    {{(void (*)(PublicTransport *))V_TaxiDestructor,
      (void (*)(PublicTransport *))V_TaxiDisplay}};

void TaxiConstructor(Taxi *p_this)
{
    PTConstructor(&(p_this->p_public_transport));
    p_this->p_public_transport.v_ptr = (VTable *)&g_VTable_Taxi;

    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *p_this, Taxi *copy)
{
    PTCCtor(&(p_this->p_public_transport), &(copy->p_public_transport));
    copy->p_public_transport = p_this->p_public_transport;

    printf("Taxi::CCtor()\n");
}

/*****                           SpecialTaxi:                             *****/

struct vtable_specialT
{
    VTable p_vtable;
};

typedef struct specialTaxi
{
    Taxi p_taxi;

} SpecialTaxi;

void V_SpecialTDestructor(SpecialTaxi *p_this)
{
    printf("SpecialTaxi::Dtor()\n");

    V_TaxiDestructor(&(p_this->p_taxi));
}

void V_SpecialTDisplay(SpecialTaxi *p_this)
{
    printf("SpecialTaxi::display() ID: %d\n",
           p_this->p_taxi.p_public_transport.m_liscence_plate);
}

struct vtable_specialT g_VTable_specialTaxi =
    {{(void (*)(PublicTransport *))V_SpecialTDestructor,
      (void (*)(PublicTransport *))V_SpecialTDisplay}};

void SpecialTConstructor(SpecialTaxi *p_this)
{
    TaxiConstructor(&(p_this->p_taxi));
    p_this->p_taxi.p_public_transport.v_ptr = (VTable *)&g_VTable_specialTaxi;

    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTCCtor(SpecialTaxi *p_this, SpecialTaxi *copy)
{
    copy->p_taxi = p_this->p_taxi;

    printf("SpecialTaxi::CCtor()\n");
}

/*****                    print_info() functions:                         *****/

void PTPrintInfo(PublicTransport *p_this)
{
    V_PTDisplay(p_this);
}

void PrintInfo(PublicTransport *p_this)
{
    S_PTPrintCount(p_this);
}

void MinibusPrintInfo(Minibus *p_this)
{
    V_MinibusWash(p_this, 3);
}

PublicTransport *Print_Info(Minibus *p_this, int i)
{
    printf("print_info(int i)\n");
    p_this->p_public_transport.v_ptr->V_Display(&(p_this->p_public_transport));

    PublicTransport *p_ptr = (PublicTransport *)malloc(sizeof(PublicTransport));

    if (NULL == p_ptr)
    {
        return (NULL);
    }

    PTCCtor(p_ptr, (PublicTransport *)p_this);

    return (p_ptr);
}

void TaxiDisplay(Taxi *s)
{
    V_TaxiDisplay(s);
}

/*****                             Main:                                  *****/

int main() /* Original cpp code is in comments inside main function: */
{
    /*Minibus m;*/
    Minibus m;
    MinibusConstructor(&m);

    /*print_info(m);*/
    MinibusPrintInfo(&m);

    /*print_info(3).display();*/
    Minibus ret;
    MinibusConstructor(&ret);
    PublicTransport *p_ret = Print_Info(&ret, 3);
    V_MinibusDestructor(&ret);
    p_ret->v_ptr->V_Display(p_ret);
    V_PTDestructor(p_ret);
    free(p_ret);
    p_ret = NULL;

    /*V_MinibusDestructor(&m);*/
    /* PublicTransport *array[] = {new Minibus(), new Taxi(), new Minibus()}; */
    Minibus *index1 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == index1)
    {
        return (1);
    }
    MinibusConstructor(index1);

    Taxi *index2 = (Taxi *)malloc(sizeof(Taxi));
    if (NULL == index2)
    {
        free(index1);
        index1 = NULL;
        return (1);
    }
    TaxiConstructor(index2);

    Minibus *index3 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == index3)
    {
        free(index1);
        index1 = NULL;
        free(index2);
        index2 = NULL;
        return (1);
    }
    MinibusConstructor(index3);

    PublicTransport *array[3] = {(PublicTransport *)index1,
                                 (PublicTransport *)index2,
                                 (PublicTransport *)index3};

    /* for (int i = 0; i < 3; ++i)
    {
        array[i]->display();
    } */
    array[0]->v_ptr->V_Display(array[0]);
    array[1]->v_ptr->V_Display(array[1]);
    array[2]->v_ptr->V_Display(array[2]);

    /* for (int i = 0; i < 3; ++i)
    {
        delete array[i];
    } */

    array[0]->v_ptr->V_Destructor(array[0]);
    array[1]->v_ptr->V_Destructor(array[1]);
    array[2]->v_ptr->V_Destructor(array[2]);

    int i = 0;
    for (i = 0; i < 3; ++i)
    {
        free(array[i]);
        array[i] = NULL;
    }

    /* PublicTransport arr2[] = {Minibus(), Taxi(), PublicTransport()}; */
    Minibus main_index1;
    MinibusConstructor(&main_index1);
    PublicTransport PTindex1;
    PTCCtor(&PTindex1, (PublicTransport *)&main_index1);
    V_MinibusDestructor(&main_index1);

    Taxi main_index2;
    TaxiConstructor(&main_index2);
    PublicTransport PTindex2;
    PTCCtor(&PTindex2, (PublicTransport *)&main_index2);
    V_TaxiDestructor(&main_index2);

    PublicTransport main_index3;
    PTConstructor(&main_index3);

    PublicTransport arr2[3] = {PTindex1, PTindex2, main_index3};

    /* for (int i = 0; i < 3; ++i)
    {
        arr2[i].display();
    } */

    PTindex1.v_ptr->V_Display(&PTindex1);
    PTindex2.v_ptr->V_Display(&PTindex2);
    main_index3.v_ptr->V_Display(&main_index3);

    /* print_info(arr2[0]); */
    PTPrintInfo(&arr2[0]);

    /* PublicTransport::print_count(); */
    S_PTPrintCount();

    /* Minibus m2; */
    Minibus m2;
    MinibusConstructor(&m2);

    /* m2.print_count(); */
    S_PTPrintCount();

    /* Minibus arr3[4]; */
    Minibus min_index1;
    MinibusConstructor(&min_index1);

    Minibus min_index2;
    MinibusConstructor(&min_index2);

    Minibus min_index3;
    MinibusConstructor(&min_index3);

    Minibus min_index4;
    MinibusConstructor(&min_index4);

    Minibus arr3[4] = {min_index1, min_index2, min_index3, min_index4};

    /* Taxi *arr4 = new Taxi[4]; */
    Taxi *arr4 = (Taxi *)malloc(sizeof(Taxi) * 4);
    if (NULL == arr4)
    {
        return (1);
    }

    for (i = 0; i < 4; ++i)
    {
        TaxiConstructor(&arr4[0]);
    }

    for (i = 0; i < 4; ++i)
    {
        V_TaxiDestructor(&arr4[i]);
    }

    /* delete[] arr4; */
    free(arr4);
    arr4 = NULL;
    /**/
    /* std::cout << max_func(1, 2) << "\n"; */
    printf("%d\n", max_func(1, 2));

    /* std::cout << max_func<int>(1, 2.0f) << "\n"; */
    printf("%d\n", max_func(1, 2));

    /* SpecialTaxi st; */
    SpecialTaxi st;
    SpecialTConstructor(&st);

    /* taxi_display(st); */
    Taxi temp;
    TaxiCCtor((Taxi *)&st, &temp);
    TaxiDisplay((Taxi *)&st);
    V_TaxiDestructor(&temp);
    V_SpecialTDestructor(&st);
    /*st.p_taxi.p_public_transport.v_ptr->V_Destructor(&st);*/

    /* Destructors: */
    V_MinibusDestructor(&min_index4);
    V_MinibusDestructor(&min_index3);
    V_MinibusDestructor(&min_index2);
    V_MinibusDestructor(&min_index1);
    V_MinibusDestructor(&m2);
    V_PTDestructor(&PTindex1);
    V_PTDestructor(&PTindex2);
    V_PTDestructor(&main_index3);
    V_MinibusDestructor(&m);

    return (0);
}
