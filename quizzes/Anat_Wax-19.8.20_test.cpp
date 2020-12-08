/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream> // cout, cin, cerr

using namespace ilrd;

#include "Anat_Wax-19.8.20.hpp"

class FuncFunctor
{
public:
    void operator()()
    {
        cout << "Horray, it worked!" << endl;
    }
};

int main()
{
    int num_threads = 5;
    int index = 0;
    boost::thread threads[5];
    SmartLock< std::ref(FuncFunctor) > smart_lock(num_threads);

    for (index = 0; index < num_threads; ++index)
    {
        threads[index](smart_lock.CheckIn()));
    }

    for (index = 0; index < num_threads; ++index)
    {
        threads[index].join();
    }

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
