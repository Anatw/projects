/*******************************************************************************
WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <stdlib.h> // system()
#include <assert.h> // assert()

#include "shared_pointer.hpp"

using namespace std;
using namespace ILRD_8586_infinty;

struct Test
{
    Test() : m_c('A'), m_i(10) {}
    char m_c;
    int m_i;
};

struct TestDerived : public Test
{
    TestDerived() : Test(), m_f(1.5) {}
    float m_f;
};

void foo(SharedPointer<int> fo)
{
    std::cout << "fo counter: " << fo.GetCounter() << std::endl;
}

SharedPointer<int> foo2()
{
    SharedPointer<int> fo2(new int(7));
    return (fo2);
}

int main()
{
    system("clear");

    SharedPointer<Test> test_SP(new Test());
    SharedPointer<int> int_SP(new int(100));

    // Notice: Besides initialization, usage of the pointers is with the usual
    //         syntax. Except one thing: User does not need to ever delete.
    // i.e, support operator=, cctor, ->, *
    test_SP->m_c = 'B';
    test_SP->m_i = 11;
    *int_SP = 111;
    SharedPointer<int> another_int_SP(new int(200));
    another_int_SP = int_SP;
    foo(int_SP);
    another_int_SP = foo2();

    // Implicit upcast work (as it is while using regular pointers):
    SharedPointer<TestDerived> test_sp_Derived(new TestDerived());
    SharedPointer<Test> test_SP_implicit_conversion(test_sp_Derived);
    SharedPointer<Test> test_SP_implicit_conversion2(NULL);
    test_SP_implicit_conversion2 = test_sp_Derived;
    test_SP_implicit_conversion2->m_c = 'C';
    assert(test_SP_implicit_conversion->m_c == 'C');
    assert(test_SP_implicit_conversion2->m_c == 'C');
    assert(test_sp_Derived->m_c == 'C');

    // Implicit downcast does NOT work (as it is while using regular pointers):
    SharedPointer<Test> test_SP_implicit_conversion_again(new Test());
    // This line need to not compile (think why):
    /* SharedPointer<TestDerived> test_SP_Derived_again(test_SP_implicit_conversion_again);*/

    // Notice - no delete required.

    return 0;
}

//     Point p(5, 6);
//     SharedPointer<Point> sp(&p);
//     cout << sp.GetCounter() << endl;
//     SharedPointer<Point> sp2(sp);
//     cout << sp.GetCounter() << endl;

//     return (0);
// }
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
// What happens when we delete the "base" pointer that hold the actual data? how will the data be transferred to an inheriting pointer;
