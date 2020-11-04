/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values

#include "udp_communicator.hpp"
#include "master_storage_manager.hpp"

using namespace ilrd;

#define PORT (5699)

int main()
{
    ReactorListener listener;
    Reactor reactor(&listener);
    MasterStorageManager master_storage_manager(4, 10);
    UDPcommunicator udp_communicator(PORT, reactor, master_storage_manager);


    return 0;
}