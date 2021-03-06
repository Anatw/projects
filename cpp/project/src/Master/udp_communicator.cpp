/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax anatwax@gmail.com
Reviewer: 
Datecreation: 20.10.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <sys/inotify.h> // inotify_init()
#include <sys/socket.h>
#include <sys/types.h>  /* getaddrinfo() */
#include <arpa/inet.h>

#include "udp_communicator.hpp"

#define DNDBUG

using namespace ilrd;


////////////////////////////////////////////////////////////////////////////////
//                      UDPcommunicator methods:                              //
////////////////////////////////////////////////////////////////////////////////

void UDPcommunicator::StartMasterReactor()
{
    LOG_INFO(__FILE__ + std::string("::StartMasterReactor() - starting the reactor"));

    m_reactor.Run();
}

//////////////////////////////////////////

void UDPcommunicator::CheckMinionsStatus(int irrelevant)
{
    (void)irrelevant;

    std::map<std::string, boost::shared_ptr<UDPMinion> >::const_iterator iterator = m_udp_minions.begin();
    std::map<std::string, boost::shared_ptr<UDPMinion> >::const_iterator end = m_udp_minions.end();

    std::vector< boost::shared_ptr< MinionInfo >  > bad_minions;

    for (; iterator != end; ++iterator)
    {
        if (iterator->second->GetStatus() == false)
        {
            bad_minions.push_back(iterator->second);
        }

        // Set Minion's status to false for the next broadcast round:
        iterator->second->SetStatus(false);
    }

    for (size_t i = 0; i < bad_minions.size(); ++i)
    {
        m_storage_manager.UnregisterMinion(bad_minions[i]);
    }

    // push again the broadcast task (every task is only executed once):
    m_scheduler.ScheduleAction(Scheduler::MS(5000), boost::bind(&UDPcommunicator::CheckMinionsStatus, this, _1));
}

//////////////////////////////////////////

// Every second a broadcast will be sent. The Master's reactor will listen to any responses. When a responase arives, it will check the map - if this minion is inside the map it will set it's status to active. If it is not in the map, it will create a new minion and will add it to the map.
// Every five seconds the map will be iterated and the Minions statuses will be checked - every minion with inactive status will be handeled.
UDPcommunicator::UDPcommunicator(int port, Reactor &reactor, MasterStorageManager &storage_manager) : m_fd(socket(AF_INET, SOCK_DGRAM, 0)), m_port(port), m_reactor(reactor), m_scheduler(m_reactor), m_storage_manager(storage_manager), m_master_broadcaster(m_port, m_scheduler)
{
    if (0 > m_fd)
    {
        LOG_ERROR(__FILE__ + std::string("::UDPcommunicator - Failed to inotify in dir_monitor.cpp"));
        std::cout << "Failed to create a socketin UDPcommunicator ctor" << std::endl;
    }

    // this Method will be activated when the broadcast fd is on - a response from a Minion has arrived
    m_reactor.Add(HandleAndMode(READ, m_master_broadcaster.GetFd()), (new Callback< SimpleSrc<int> >(boost::bind(&UDPcommunicator::OnMinionReply, this, _1))));

    m_reactor_thread = boost::thread(boost::bind(&UDPcommunicator::StartMasterReactor, this));

    // Add a new method to the scheduler: check map every 5 seconds - make a list of all "not-active" Minions and send it to the master storage manager:
    m_scheduler.ScheduleAction(Scheduler::MS(5000), boost::bind(&UDPcommunicator::CheckMinionsStatus, this, _1)); 
}

//////////////////////////////////////////

// This function will be called when a minion respond to the udp broadcast the Master's UDPcommunicator has sent
void UDPcommunicator::OnMinionReply(int fd)
{
    struct sockaddr_in minion_addr; 
    memset(&minion_addr, 0, sizeof(sockaddr_in));
    BroadcastFrom from_minion;
    int sockaddr_size = sizeof(sockaddr_in);

    int status = recvfrom(fd, (char *)&from_minion, sizeof(BroadcastFrom), MSG_WAITALL, (struct sockaddr *)&minion_addr, (socklen_t *)&sockaddr_size);
    if (status < 0)
    {
        LOG_ERROR(__FILE__ + std::string("::OnMinionReply() - Error in receieving from minion"));
    }

    // Create a new UDPMinion and check the response type: 
    boost::shared_ptr< UDPMinion >minion(new UDPMinion(m_master_broadcaster.GetFd(), m_port, inet_ntoa(minion_addr.sin_addr)));

    switch (from_minion.m_type)    
    {
        case ('b') : // Broadcast response from Minion
        {
            // If minion replied with broadcast it mean that we are connected and that this is his master, so the Minion's status in the list should be set to true:
            std::map<std::string, boost::shared_ptr<UDPMinion> >::iterator iterator = m_udp_minions.find(inet_ntoa(minion_addr.sin_addr));
            if (iterator != m_udp_minions.end()) // This Minion is in the map
            {
                iterator->second->SetStatus(true);
            }
            else
            {
                // Check if Master storage need new minion:
                if (m_storage_manager.ShouldAddMinion() == true)
                {
                    // Send an attach request to minion:
                    AssigmentRequest assignment_req;
                    assignment_req.m_uid_master = m_master_broadcaster.GetUID();
                    assignment_req.m_uid_minion = from_minion.m_uid_from;
                    assignment_req.m_type = 'a';
                }
            }

            break;
        }
        case ('a') : // Attach request from Minion
        {
            minion->SetStatus(true);
            m_udp_minions.insert(std::make_pair(minion->GetIp(), minion));

            m_storage_manager.RegisterNewMinion(minion);

            break;
        }
        case ('d') : // Detach request from Minion
        {
            // Find the Minion in the map, set it's status to false (not working), erase it from the map, and unregister it from the storage:
            std::map<std::string, boost::shared_ptr<UDPMinion> >::iterator iterator = m_udp_minions.find(inet_ntoa(minion_addr.sin_addr));

            iterator->second->SetStatus(false);

            m_udp_minions.erase(inet_ntoa(minion_addr.sin_addr));
            m_storage_manager.UnregisterMinion(minion);

            break;
        }
    }    
}

//////////////////////////////////////////

UDPcommunicator::~UDPcommunicator()
{
    close(m_fd); // Close the socket
    m_reactor_thread.join();
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                          UDPMinion methods:                                //
////////////////////////////////////////////////////////////////////////////////

UDPcommunicator::UDPMinion::UDPMinion(int fd, int port, const std::string &ip) : m_fd(fd), m_port(port), m_ip(ip)
{
}

//////////////////////////////////////////

void UDPcommunicator::UDPMinion::Send(char* data)
{
    struct sockaddr_in master_addres;
    memset(&master_addres, 0, sizeof(master_addres));
    master_addres.sin_family = AF_INET;
    master_addres.sin_addr.s_addr = htonl(INADDR_ANY);
    master_addres.sin_port = htons(m_port);

    if (0 > sendto(m_fd, data, sizeof(data), MSG_CONFIRM, (const struct sockaddr *) &master_addres, sizeof(sockaddr_in)))
    {
        LOG_ERROR(__FILE__ + std::string("::UDPMinion::Send() - sendto() failed"));
        throw std::runtime_error("error in UDPMinion (Send())");
    }
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                      Broadcaster methods:                                  //
////////////////////////////////////////////////////////////////////////////////

// Sending a udp broadcast to all the network. Only Minions that are connected to the currently sending master or Minions that are not connected to any master will respond to the broadcast
// The broadcaster is the client - he is the first to send the massage.
void UDPcommunicator::Broadcaster::SendBroadCast(int irrelevant)
{
    (void)irrelevant;
    // Generate a unique uid for the master:
    const UID temp_uid = boost::uuids::random_generator()();
    memcpy(&m_master_uid, &temp_uid, sizeof(UID));

    int broadcastPermission = 1; /* Socket opt to set permission to broadcast */
    /* Create socket for sending/receiving datagrams */
    if (0 > (m_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        LOG_ERROR(__FILE__ + std::string("UDPcommunicator::Broadcaster::SendBroadCast() : ERROR in socket()"));
    }
    /* Set socket to allow broadcast */
    if (0 > (setsockopt(m_fd,
                        SOL_SOCKET,
                        SO_BROADCAST,
                        &broadcastPermission,
                        sizeof(broadcastPermission))))
    {
        LOG_ERROR(__FILE__ + std::string("UDPcommunicator::Broadcaster::SendBroadCast() : ERROR in setsockopt()"));
    }

    struct sockaddr_in master_address; /* Broadcast address */
    memset(&master_address, 0, sizeof(master_address));
    // address family: AF_INET:
    master_address.sin_family = AF_INET; 
    // port in network byte order - this is why the "htons" is there...:
    master_address.sin_port = htons(m_port);
    master_address.sin_addr.s_addr = INADDR_BROADCAST;

    struct sockaddr_in receieve_address;

    BroadcastFrom *massage = new BroadcastFrom;
    massage->m_uid_from = m_master_uid;
    boost::uuids::nil_generator uid_zero;
    massage->m_uid_not_relevant = uid_zero();
    massage->m_type = 'b';

    UID::iterator iterator = GetUID().begin();
    UID::iterator end = GetUID().end();
    std::cout << "inside master - massage type:" << massage->m_type << std::endl;
    for (; iterator != end; ++iterator)
    {
        std::cout << *iterator << std::endl;
    }


    sendto(m_fd,massage,sizeof(BroadcastFrom),MSG_CONFIRM,(sockaddr *)&master_address,sizeof(master_address));
    
    // push again the broadcast task (every task is only executed once):
    m_scheduler.ScheduleAction(Scheduler::MS(1000), boost::bind(&Broadcaster::SendBroadCast, this, _1));

    delete massage;
}

//////////////////////////////////////////

UDPcommunicator::Broadcaster::Broadcaster(int port, Scheduler &scheduler) : m_port(port), m_is_on(true), m_scheduler(scheduler)
{
    // creating a udp socket:
    if (0 > (m_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        LOG_ERROR("Failed to inotify in dir_monitor.cpp");
        std::cout << "Failed to inotify in dir_monitor.cpp" << std::endl;
    }
    
    // Send a broadcast every 1 second:
    m_scheduler.ScheduleAction(Scheduler::MS(1000), boost::bind(&Broadcaster::SendBroadCast, this, _1));
}

//////////////////////////////////////////

UDPcommunicator::Broadcaster::~Broadcaster()
{
    m_is_on = false;
    close(m_fd);
}

