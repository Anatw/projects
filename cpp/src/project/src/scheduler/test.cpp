/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include <sys/timerfd.h>

using namespace std;

int main()
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);

    cout << "fd = " << fd << endl;

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
