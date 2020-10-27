/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <sys/inotify.h> // inotify_init()
#include <sys/socket.h>
#include <sys/types.h>  /* getaddrinfo() */
#include <arpa/inet.h>

#include "udp_communicator.hpp"

using namespace ilrd;



UDPcommunicator::UDPMinion::UDPMinion(int fd, int port, const std::string &ip) : m_fd(fd), m_port(port), m_ip(ip)
{
    
}

////////////////////////////////////////////////////////////////////////////////

// Sending a udp broadcast to all the network. Only Minions that are connected to the currently sending master or Minions that are not connected to any master will respond to the broadcast
void UDPcommunicator::Broadcaster::SendBroadCast()
{
    struct sockaddr_in master_address;
    memset(&master_address, 0, sizeof(master_address));
    // address family: AF_INET:
    master_address.sin_family = AF_INET; 
    // port in network byte order - this is why the "htons" is there...:
    master_address.sin_port = htons(m_port);
    master_address.sin_addr.s_addr = INADDR_BROADCAST;

    struct sockaddr_in receieve_address;

    BroadcastFrom massage;
    massage.m_uid_from = 533422123;
    massage.m_type = 'b';

    sendto(m_fd,massage,sizeof(BroadcastFrom),0,(sockaddr *)&receieve_address,sizeof(receieve_address));
}

UDPcommunicator::Broadcaster::Broadcaster(int port) : m_port(port), m_is_on(true), m_sending_thread(boost::bind(&SendBroadCast, this))
{
    m_fd = socket(AF_INET, SOCK_DGRAM, 0); // creating a udp socket

    if (0 > m_fd)
    {
        LOG_ERROR("Failed to inotify in dir_monitor.cpp");
        std::cout << "Failed to inotify in dir_monitor.cpp" << std::endl;
    }

}

////////////////////////////////////////////////////////////////////////////////

UDPcommunicator::UDPcommunicator(int port, Reactor &reactor, MasterStorageManager &storage_manager) : m_port(port), m_reactor(reactor), m_storage_manager(storage_manager)
{

}