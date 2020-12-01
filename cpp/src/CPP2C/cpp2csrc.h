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
#ifndef ILRD_RD8586_CPP2CSRC_HPP
#define ILRD_RD8586_CPP2CSRC_HPP

/*                            PublicTransport:                                */

typedef struct publicTransport PublicTransport;

typedef struct vTable_PT VTable;

struct publicTransport;

void V_PTDestructor(PublicTransport *p_this);

void V_PTDisplay(PublicTransport *p_this);

void PTConstructor(PublicTransport *p_this);

void PTCCtor(PublicTransport *p_this, PublicTransport *copy);

void S_PTPrintCount();

int PD_PTGetID(PublicTransport *p_this);

/*****                         Mininbus:                                  *****/

typedef struct minibus Minibus;

struct Minibus_VTable;

void V_MinibusDestructor(Minibus *p_this);

void V_MinibusDisplay(Minibus *p_this);

void V_MinibusWash(Minibus *p_this, int minutes);

void MinibusConstructor(Minibus *p_this);

void MinibusCCtor(Minibus *p_this, Minibus *copy);

/*****                              Taxi:                                 *****/

struct vtable_taxi;

typedef struct taxi Taxi;

int max_func(const int t1, const int t2);

void V_TaxiDestructor(Taxi *p_this);

void V_TaxiDisplay(Taxi *p_this);

void TaxiConstructor(Taxi *p_this);

void TaxiCCtor(Taxi *p_this, Taxi *copy);

/*****                           SpecialTaxi:                             *****/

struct vtable_specialT;

typedef struct specialTaxi SpecialTaxi;

void V_SpecialTDestructor(SpecialTaxi *p_this);

void V_SpecialTDisplay(SpecialTaxi *p_this);

void SpecialTConstructor(SpecialTaxi *p_this);

void SpecialTCCtor(SpecialTaxi *p_this, SpecialTaxi *copy);

/*****                    print_info() functions:                         *****/

void PTPrintInfo(PublicTransport *p_this);

void PrintInfo(PublicTransport *p_this);

void MinibusPrintInfo(Minibus *p_this);

PublicTransport *Print_Info(Minibus *p_this, int i);

void TaxiDisplay(Taxi *s);

#endif /* ILRD_RD8586_CPP2CSRC_HPP */
