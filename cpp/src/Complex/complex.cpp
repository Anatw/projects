/*******************************************************************************
                                Complex
                          Written by Anat Wax
						     June 2nd, 2020
						Reviewer: Ivanna Fleisher
*******************************************************************************/
#include <iostream>      // cout, cin, cerr
#include <bits/stdc++.h> // clock()
using namespace std;

#include "complex.hpp"

#define Q1

/*******************************************************************************
                              Ctores + Dtor:
*******************************************************************************/
Complex::Complex() : real(0), imeg(0)
{
}

Complex::Complex(int n_, int m_) : real(n_), imeg(m_)
{
}

Complex::Complex(const Complex &o_)
{
    this->real = o_.real;
    this->imeg = o_.imeg;
}

Complex &Complex::operator=(const Complex &other_)
{
    this->real = other_.real;
    this->imeg = other_.imeg;

    return (*this);
}

Complex::~Complex() {}

/*******************************************************************************
                                Operators:
*******************************************************************************/
Complex Complex::operator+(const Complex &second_)
{
    Complex result;
    result.real = this->real + second_.real;
    result.imeg = this->imeg + second_.imeg;

    return (result);
}

#ifndef Q1 // by value
Complex Complex::operator+(const Complex second_)
{
    Complex result;
    result.real = this->real + second_.real;
    result.imeg = this->imeg + second_.imeg;

    return (result);
}
#endif

Complex Complex::operator-(const Complex &second_)
{
    Complex result;
    result.real = this->real - second_.real;
    result.imeg = this->imeg - second_.imeg;

    return (result);
}

Complex Complex::operator*(const Complex &second_)
{
    Complex result;
    result.real = (this->real * second_.real) - (this->imeg * second_.imeg);
    result.imeg = (this->real * second_.imeg) - (second_.real * this->imeg);

    return (result);
}

Complex Complex::operator/(const Complex &second_)
{
    Complex result;
    result.real = (this->real * second_.real + this->imeg * second_.imeg) /
                  (second_.real * second_.real + second_.imeg * second_.imeg);
    result.imeg = (this->imeg * second_.real + this->real * second_.imeg) /
                  (second_.real * second_.real + second_.imeg * second_.imeg);
    return (result);
}

bool Complex::operator==(const Complex &second_)
{
    return (this->real == second_.real && this->imeg == second_.imeg);
}

bool Complex::operator!=(const Complex &second_)
{
    return (this->real != second_.real || this->imeg != second_.imeg);
}

ostream &operator<<(ostream &ostr_, const Complex &second_)
{

    return (ostr_ << "(" << second_.real << ", " << second_.imeg << ")" << endl);
}

istream &operator>>(istream &istr_, Complex &num_)
{
    return (istr_ >> num_.real >> num_.imeg);
}
