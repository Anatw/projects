/*******************************************************************************
Templates + STL (Point)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: Noffar Gil
*******************************************************************************/
#include <iostream> /* cout, cin, cerr */
#include <cassert>  // assert()

#include "t_point.hpp"

void CheckInt();
void CheckDouble();
void CheckChar();
void CheckFloat();

////////////////////////////////////////////////////////////////////////////////
//                                   Main:                                   //
////////////////////////////////////////////////////////////////////////////////

int main()
{
    CheckInt();
    CheckDouble();
    CheckChar();

    return (0);
}

void CheckInt()
{
    Point<int> first(10, 5);
    Point<int> second(6, 15);

    Point<int> third = first + second;
    assert(third.GetX() == 16);
    assert(third.GetY() == 20);

    first += second;
    assert(first.GetX() == 16);
    assert(first.GetY() == 20);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckDouble()
{
    Point<double> first(10.5, 5.5);
    Point<double> second(6.5, 15.5);

    Point<double> third = first + second;
    assert(third.GetX() == 17);
    assert(third.GetY() == 21);

    first += second;
    assert(first.GetX() == 17);
    assert(first.GetY() == 21);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckChar()
{
    Point<unsigned char> first('a', 'b');  // (97, 98)
    Point<unsigned char> second('c', 'd'); // (99, 100)

    Point<unsigned char> third = first + second;
    assert(third.GetX() == 196);
    assert(third.GetY() == 198);

    first += second;
    assert(first.GetX() == 196);
    assert(first.GetY() == 198);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}

void CheckFloat()
{
    Point<float> first(10.5, 5.5);
    Point<float> second(6.5, 15.5);

    Point<float> third = first + second;
    assert(third.GetX() == 17);
    assert(third.GetY() == 21);

    first += second;
    assert(first.GetX() == 17);
    assert(first.GetY() == 21);

    third -= first;
    assert(third.GetX() == 0);
    assert(third.GetY() == 0);
}
