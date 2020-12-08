/*******************************************************************************
Comment and un-comment the defines to see both phases.

                                Complex
                          Written by Anat Wax
						     June 2nd, 2020
						Reviewer: Ivanna Fleisher
*******************************************************************************/
#include <bits/stdc++.h> // clock()

#include "complex.hpp"

/*******************************************************************************
                                Main:
*******************************************************************************/
int main()
{
    Complex obj1;
    Complex obj2(4);
    Complex obj3(5, 8);

    clock_t start;
    clock_t end;

    cout << obj1 << endl;
    cout << obj2 << endl;
    cout << obj3 << endl;

    cout << "Enter two nnmbers to replace real and imeg:" << endl;
    cin >> obj3;
    cout << obj1 << endl;
    cout << obj3 << endl;

    obj1.SetReal(80);
    cout << obj1 << endl;
    cout << obj3.GetImaginary() << endl;

    start = clock();
    for (int i = 0; i < 100000; ++i)
    {
        obj3 = obj3 + obj2;
    }
    end = clock();
    cout << obj3 << endl;

    double time_to_run = double(end - start) / double(CLOCKS_PER_SEC);

    cout << "Time elapsed: " << fixed << time_to_run << setprecision(5) << endl;

    return (0);
}

/*
With optimization:
By reference:
Time elapsed: 0.001605

By value:
Time elapsed: 0.001789

Without optimization:
By reference:
Time elapsed: 0.000540

By value:
Time elapsed: 0.000328
*/
