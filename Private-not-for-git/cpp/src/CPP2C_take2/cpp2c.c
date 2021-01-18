/*******************************************************************************
all printf() of numbers that exist inside this file are not inside the original
CPP code and are here only to help me eith the exercise.

cpp2c.cpp->c file
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <stdio.h>    /* printf(), size_t */
#include <stdlib.h>   /* malloc(), free(), abs(), size_t */
#include <unistd.h>   /* ssize_t, sleep(), execvp(), fork() */
#include <string.h>   /* size_t, atoi(), memset() */
#include <sys/wait.h> /* wait() */

static int s_count = 0;

typedef struct publicTransport PublicTransport;

typedef struct vTable
{
    void (*V_Destructor)(PublicTransport *p_this);
    void (*V_Display)(PublicTransport *p_this);
} Vtable;

struct publicTransport
{
    Vtable *vptr;
    int m_license_plate;
};

typedef struct minibus
{
    PublicTransport m_pt;
    int m_numSeats;
} Minibus;

typedef struct taxi
{
    PublicTransport m_pt;
} Taxi;

typedef struct specialTaxi
{
    Taxi m_taxi;
} SpecialTaxi;

typedef struct publicConvoy
{
    PublicTransport m_pt;

    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
} PC;

/*******************************************************************************
 *                        Public transport functions:                         *
/******************************************************************************/

void V_PTDestructor(PublicTransport *p_this)
{
    p_this->m_license_plate = s_count;
    --s_count;
    printf("PublicTransport::Dtor() %d\n", p_this->m_license_plate);
}

void V_PTDisplay(PublicTransport *p_this)
{
    printf("PublicTransport::display(): %d\n", p_this->m_license_plate);
}

Vtable PT_Vtable = {V_PTDestructor, V_PTDisplay};

void PTConstructor(PublicTransport *p_this)
{
    p_this->vptr = &PT_Vtable;

    ++s_count;
    p_this->m_license_plate = s_count;

    printf("PublicTransport::Ctor() %d\n", p_this->m_license_plate);
}

const PublicTransport PTCctor(PublicTransport *p_this, PublicTransport *other)
{
    p_this->vptr = &PT_Vtable;

    ++s_count;
    p_this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", p_this->m_license_plate);
}

void print_count()
{
    printf("s_count: %d\n", s_count);
}

int get_ID(PublicTransport *p_this)
{
    return (p_this->m_license_plate);
}

/*******************************************************************************
 *                          Minibus functions:                                *
/******************************************************************************/

void MinibusDestructor(Minibus *p_this)
{
    printf("Minibus::Dtor()\n");

    V_PTDestructor(&p_this->m_pt);
}

void MinibusDisplay(Minibus *p_this)
{
    printf("Minibus::display() ID: %d", get_ID(&(p_this->m_pt)));
    printf(" num seats: %d\n", p_this->m_numSeats);
}

void V_MinibusWash(Minibus *p_this, int minutes)

{
    printf("Minibus::wash(%d) ID: %d\n", minutes, get_ID(&(p_this->m_pt)));
}

struct min_vtable
{
    Vtable vtable;
    void (*V_MinibusWash)(Minibus *p_this, int minutes);
};

struct min_vtable Minibus_VTable =
    {{(void (*)(PublicTransport *))MinibusDestructor,
      (void (*)(PublicTransport *))MinibusDisplay},
     V_MinibusWash};

void MinibusConstructor(Minibus *p_this)
{
    PTConstructor(&(p_this->m_pt));

    p_this->m_pt.vptr = (Vtable *)&Minibus_VTable;

    p_this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

Minibus *MinibusCctor(Minibus *p_this, Minibus *other)
{
    PTCctor(&p_this->m_pt, &other->m_pt);

    p_this->m_pt.vptr = (Vtable *)&Minibus_VTable;

    p_this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

/*******************************************************************************
 *                             Taxi functions:                                *
/******************************************************************************/

void TaxiDestructor(Taxi *p_this)
{
    printf("Taxi::Dtor()\n");

    V_PTDestructor(&p_this->m_pt);
}

void TaxiDisplay(Taxi *p_this)
{
    printf("Taxi::display() ID: %d\n", get_ID(&p_this->m_pt));
}

Vtable TaxiVtable = {(void (*)(PublicTransport *))TaxiDestructor,
                     (void (*)(PublicTransport *))TaxiDisplay};

void TaxiConstructor(Taxi *p_this)
{
    PTConstructor(&(p_this->m_pt));

    p_this->m_pt.vptr = &TaxiVtable;

    printf("Taxi::Ctor()\n");
}

Taxi *TaxiCctor(Taxi *p_this, Taxi *other)
{
    PTCctor(&p_this->m_pt, &other->m_pt);
    p_this->m_pt.vptr = other->m_pt.vptr;

    printf("Taxi::CCtor()\n");
}

/*******************************************************************************
 *                         SpecialTaxi functions:                             *
/******************************************************************************/

void STaxiDestructor(SpecialTaxi *p_this)
{

    printf("SpecialTaxi::Dtor()\n");

    TaxiDestructor((Taxi *)p_this);
}

void STaxiDisplay(SpecialTaxi *p_this)
{
    printf("SpecialTaxi::display() ID: %d\n", get_ID((PublicTransport *)p_this));
}

Vtable STaxiVtable = {(void (*)(PublicTransport *))STaxiDestructor,
                      (void (*)(PublicTransport *))STaxiDisplay};

void STaxiConstructor(SpecialTaxi *p_this)
{
    TaxiConstructor((Taxi *)p_this);

    p_this->m_taxi.m_pt.vptr = &STaxiVtable;

    printf("SpecialTaxi::Ctor()\n");
}

SpecialTaxi *STaxiCctor(SpecialTaxi *p_this, SpecialTaxi *other)
{
    TaxiCctor((Taxi *)p_this, (Taxi *)other);

    printf("SpecialTaxi::CCtor()\n");
}

/*******************************************************************************
 *                       Public Convoy functions:                             *
/******************************************************************************/
void PCDestructor(PC *p_this)
{
    /*publicConvoy *this = (publicConvoy *)p_this;*/
    V_PTDestructor(p_this->m_pt1);
    V_PTDestructor(p_this->m_pt2);

    free(p_this->m_pt1);
    p_this->m_pt1 = NULL;
    free(p_this->m_pt2);
    p_this->m_pt2 = NULL;

    MinibusDestructor(&(p_this->m_m));
    TaxiDestructor(&(p_this->m_t));

    V_PTDestructor(&(p_this->m_pt));
}

void PCDisplay(PC *p_this)
{
    p_this->m_pt1->vptr->V_Display(p_this->m_pt1);
    p_this->m_pt2->vptr->V_Display(p_this->m_pt2);
    p_this->m_m.m_pt.vptr->V_Display((PublicTransport *)&p_this->m_m);
    p_this->m_t.m_pt.vptr->V_Display((PublicTransport *)&p_this->m_t);
}

Vtable PCVtable = {(void (*)(PublicTransport *))PCDestructor,
                   (void (*)(PublicTransport *))PCDisplay};

void PCConstructor(PC *p_this)
{
    /* Creating the inherent class PT member: */
    PTConstructor(&p_this->m_pt);
    p_this->m_pt.vptr = &PCVtable;

    Minibus *pt1 = (Minibus *)malloc(sizeof(Minibus));
    MinibusConstructor(pt1);

    Taxi *pt2 = (Taxi *)malloc(sizeof(Taxi));
    TaxiConstructor(pt2);

    p_this->m_pt1 = (PublicTransport *)pt1;
    p_this->m_pt2 = (PublicTransport *)pt2;
    MinibusConstructor(&p_this->m_m);
    TaxiConstructor(&p_this->m_t);
}

PC *PCCctor(PC *p_this, PC *other)
{
    PTCctor(&p_this->m_pt, &other->m_pt);
    p_this->m_pt.vptr = &PCVtable;

    PublicTransport *pt1 = (PublicTransport *)malloc(sizeof(Minibus));
    p_this->m_pt1 = pt1;
    MinibusCctor((Minibus *)p_this->m_pt1, (Minibus *)other->m_pt1);
    /*pt1 = other->m_pt1;*/

    PublicTransport *pt2 = (PublicTransport *)malloc(sizeof(Taxi));
    p_this->m_pt2 = pt2;
    TaxiCctor((Taxi *)p_this->m_pt2, (Taxi *)other->m_pt2);
    /* pt2 = other->m_pt2;*/

    MinibusCctor(&p_this->m_m, &other->m_m);
    TaxiCctor(&p_this->m_t, &other->m_t);

    return (p_this);
}

/*******************************************************************************
 *                            other functions:                                *
/******************************************************************************/

int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

void print_info_rec_PT(PublicTransport *a)
{
    V_PTDisplay(a);
}

void print_info(PublicTransport *p_this)
{
    print_count(p_this);
}

void print_info_rec_minibus(Minibus *m)
{
    ((struct min_vtable *)m->m_pt.vptr)->V_MinibusWash(m, 3);
}

PublicTransport PrintInfo(int i)
{
    Minibus ret;
    MinibusConstructor(&ret);
    printf("print_info(int i)\n");
    MinibusDisplay(&ret);
    PublicTransport pt;
    PTCctor(&pt, &ret.m_pt);
    MinibusDestructor(&ret);

    return (pt);
}

void taxi_display(Taxi *s)
{
    printf("Taxi::display() ID: %d\n",
           get_ID(&s->m_pt));
}

/*******************************************************************************
 *                                Main:                                       *
/******************************************************************************/

int main()
{
    int i = 0;
    /* Minibus m; */
    printf("1\n");
    Minibus m;
    MinibusConstructor(&m);

    /* print_info(m); */
    printf("2\n");
    print_info_rec_minibus(&m);

    /* print_info(3).display(); */
    printf("3\n");
    PublicTransport ret = PrintInfo(3);
    V_PTDisplay(&ret);
    V_PTDestructor(&ret);

    /* PublicTransport *array[] = {new Minibus(), new Taxi(), new Minibus()}; */
    printf("4\n");
    Minibus *min1 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == min1)
    {
        return (1);
    }
    MinibusConstructor(min1);

    Taxi *taxi = (Taxi *)malloc(sizeof(Taxi));
    if (NULL == taxi)
    {
        free(min1);
        min1 = NULL;
        return (1);
    }
    TaxiConstructor(taxi);

    Minibus *min2 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == min2)
    {
        free(min1);
        min1 = NULL;
        free(taxi);
        taxi = NULL;
        return (1);
    }
    MinibusConstructor(min2);

    PublicTransport *array[] = {(PublicTransport *)min1,
                                (PublicTransport *)taxi,
                                (PublicTransport *)min2};

    /*for (int i = 0; i < 3; ++i)
    {
        array[i]->display();
    }*/
    printf("5\n");
    for (i = 0; i < 3; ++i)
    {
        array[i]->vptr->V_Display(array[i]);
    }
    /*for (int i = 0; i < 3; ++i)
    {
        delete array[i];
    }*/
    printf("6\n");
    for (i = 0; i < 3; ++i)
    {
        array[i]->vptr->V_Destructor(array[i]);
        free(array[i]);
        array[i] = NULL;
    }

    /*PublicTransport arr2[] = {Minibus(), Taxi(), PublicTransport()};*/
    printf("7\n");
    Minibus min3;
    MinibusConstructor(&min3);
    PublicTransport pt_min3;
    PTCctor(&pt_min3, &min3.m_pt);
    MinibusDestructor(&min3);

    Taxi taxi2;
    TaxiConstructor(&taxi2);
    PublicTransport pt_taxi2;
    PTCctor(&pt_taxi2, &taxi2.m_pt);
    TaxiDestructor(&taxi2);

    PublicTransport pt;
    PTConstructor(&pt);

    PublicTransport arr2[3] = {pt_min3,
                               pt_taxi2,
                               pt};

    /*for (int i = 0; i < 3; ++i)
        {
        arr2[i].display();
        } */
    printf("8\n");
    for (i = 0; i < 3; ++i)
    {
        arr2[i].vptr->V_Display(&arr2[i]);
    }

    /*print_info(arr2[0]);*/
    printf("9\n");
    print_info_rec_PT(&arr2[0]);

    /*PublicTransport::print_count();*/
    printf("10\n");
    print_count();

    /*Minibus m2;*/
    printf("11\n");
    Minibus *m2 = (Minibus *)malloc(sizeof(Minibus));
    MinibusConstructor(m2);

    /*m2.print_count();*/
    print_count();

    /*Minibus arr3[4];*/
    printf("12\n");
    Minibus arr3[4] = {0};
    for (i = 0; i <= 3; ++i)
    {
        MinibusConstructor(&arr3[i]);
    }

    /*Taxi *arr4 = new Taxi[4];*/
    printf("13\n");
    Taxi *arr4 = (Taxi *)malloc((sizeof(Taxi)) * 4);
    for (i = 0; i <= 3; ++i)
    {
        TaxiConstructor(&arr4[i]);
    }

    /*delete[] arr4;*/
    printf("14\n");

    for (i = 0; i < 3; ++i)
    {
        TaxiDestructor(&arr4[i]);
    }

    TaxiDestructor(arr4);

    free(arr4);
    arr4 = NULL;

    /*std::cout << max_func(1, 2) << "\n";*/
    printf("%d\n", max_func(1, 2));

    /*std::cout << max_func<int>(1, 2.0f) << "\n";*/
    printf("%d\n", max_func(1, 2));

    /*SpecialTaxi st;*/
    printf("15\n");
    SpecialTaxi st;
    STaxiConstructor(&st);

    /*taxi_display(st);*/
    printf("16\n");
    Taxi temp;
    TaxiCctor(&temp, (Taxi *)&st);
    taxi_display(&temp);
    TaxiDestructor(&temp);
    STaxiDestructor(&st);

    printf("\n\nStarting Public Convoy area:\n");
    /* PublicConvoy *ts1 = new PublicConvoy();*/
    printf("17\n");
    PC *ts1 = (PC *)malloc(sizeof(PC));
    PCConstructor(ts1);

    /* PublicConvoy *ts2 = new PublicConvoy(*ts1); */
    printf("18\n");
    PC *ts2 = (PC *)malloc(sizeof(PC));
    PCCctor(ts2, ts1);

    /* ts1->display(); */
    printf("19\n");
    ts1->m_pt.vptr->V_Display((PublicTransport *)ts1);

    /* ts2->display();*/
    printf("20\n");
    ts2->m_pt.vptr->V_Display((PublicTransport *)ts2);

    /* delete ts1; */
    printf("21\n");
    PCDestructor(ts1);
    free(ts1);

    /* ts2->display(); */
    printf("22\n");
    ts2->m_pt.vptr->V_Display(&ts2->m_pt);

    /* delete ts2; */
    printf("23\n");
    PCDestructor(ts2);
    free(ts2);

    for (i = 0; i <= 3; ++i)
    {
        MinibusDestructor(&arr3[i]);
    }

    MinibusDestructor(m2);
    free(m2);
    m2 = NULL;
    V_PTDestructor(&pt_min3);
    V_PTDestructor(&pt_taxi2);
    V_PTDestructor(&pt);
    MinibusDestructor(&m);

    return (0);
}
