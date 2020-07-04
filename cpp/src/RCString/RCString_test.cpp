/*******************************************************************************
                                RCString
                          Written by Anat Wax
						     June 4-7th, 2020
						Reviewer: Kobi Rappaport
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "RCString.hpp"

using namespace std;

int main()
{
    RCString s1("hello"); //  s1 now equals to "hello".
    cout << "s1 length is: " << s1.Length() << endl;
    // Create new RCString object called 's2',
    // which is actually a copy of s1 (contains "hello"):
    RCString s2(s1);

    s1 = s2; // s2 is a copy of s1 (contains "hello").
    cout << "s2 length is: " << s2.Length() << endl;

    s1 = s1;
    s1.ToCStr(); // return m_cstr
    cout << s1.ToCStr() << endl;
    cout << s1.ToCStr() << endl;

    RCString s3 = " world!";

    RCString s4 = s2.Concat(s3);
    //cout << "s4: " << s4 << endl;
    cout << s4 << endl;
    cout << s1.ToCStr() << endl;
    RCString s5 = s3.Concat(s2);
    cout << s5 << endl;

    return (0);
}
