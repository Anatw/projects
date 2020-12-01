/*******************************************************************************
Comment and un-comment the defines to see both phases.

                                Complex
                          Written by Anat Wax
						     June 2nd, 2020
						Reviewer: Ivanna Fleisher
*******************************************************************************/
#ifndef ILRD_RD8586_COMPLEX_HPP
#define ILRD_RD8586_COMPLEX_HPP
#include <iostream> /* cout, cin, cerr */

using namespace std;

#define Q1

class Complex
{
public:
    Complex();
    Complex(int real, int imeg = 0);
    Complex(const Complex &o_);
    ~Complex();

    Complex &operator=(const Complex &other_); // Assignment Ctor
    Complex operator+(const Complex &second_);
    Complex operator-(const Complex &second_);
    Complex operator*(const Complex &second_);
    Complex operator/(const Complex &second_);

    bool operator==(const Complex &second_);
    bool operator!=(const Complex &second_);

    friend ostream &operator<<(ostream &ostr_, const Complex &second_);
    friend istream &operator>>(istream &istr_, Complex &num_);

    inline void SetReal(int data)
    {
        this->real = data;
    }

    inline void SetImaginary(int data)
    {
        this->imeg = data;
    }

    inline int GetReal() const
    {
        return (this->real);
    }

    inline int GetImaginary() const
    {
        return (this->imeg);
    }

    void Print();

#ifndef Q1
    Complex operator+(const Complex second_);
#endif

private:
    int real;
    int imeg;
};

#endif //ILRD_RD8586_COMPLEX_HPP
