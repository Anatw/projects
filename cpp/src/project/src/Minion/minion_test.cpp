/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "minion.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    int port = 1235;
    int master_port = 4568;
    Minion minion(port, 10, master_port);

    return (0);
}
////////////////////////////////////////////////////////////////////////////////
//                           Inline functions:                                //
////////////////////////////////////////////////////////////////////////////////
