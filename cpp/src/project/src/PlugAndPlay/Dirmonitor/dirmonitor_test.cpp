/*******************************************************************************
Plug&Play - Phase 2:
Dirmonitor class

Written by Anat Wax, anatwax@gmail.com
Created: 30.8.20
Reviewer:
*******************************************************************************/

#include "advanced_observer.hpp"
#include "dirmonitor.hpp"

using namespace ilrd;

void function(std::string string)
{
    std::cout << string << std::endl;
}

int main()
{
    DirMonitor monitor(
        "/home/anat/git/anat-wax/cpp/src/project/src/PlugAndPlay/SharedObject");

    Callback< Dispatcher< std::string > > callback(function);
    monitor.Subscribe(&callback);

    monitor.StartMonitoring();

    std::cout << "I'm after the start monitoring" << std::endl;

    sleep(40);

    std::cout << "Finished" << std::endl;

    return (0);
}
