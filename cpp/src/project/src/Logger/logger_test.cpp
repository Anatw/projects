/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer:
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "logger.hpp"

using namespace ilrd;

int main()
{
    LOG_ERROR("this is an error messge");
    LOG_WARNING("this is a warning messge");
    LOG_INFO("this is an info messge");
    LOG_DEBUG("this is a debug messge");

    sleep(1);

    return (0);
}
