/*******************************************************************************
The master protocol

Authour: Anat Wax anatwax@gmail.com
Reviewer: 
Datecreation: 26.10.2020
Version: 1
*******************************************************************************/
#ifndef __ILRD_RD8586_MASTER_PROTOCOL_HPP__
#define __ILRD_RD8586_MASTER_PROTOCOL_HPP__

#include <stdlib.h>     /*  size_t */
#include <stdint.h>    /* unint_64_t */
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators

#include "uid.h"

namespace ilrd
{
    typedef boost::uuids::uuid UID;
    /*Master request :
    * m_uid_from: own id;
    * m_type: 'b' - broadcast;
    
    * Minion answer :
    * m_uid_from: own id;
    * m_type: 'b' - broadcast;
    */
    // The master will send this request - this is the broadcast that will be sent to the entire system.
    // The minion will answer to this request if he either - not connected to any master/ connected to the master that sent the broadcast.
    struct BroadcastFrom
    {
        // In my API I changed m_uid_from (and all other uid variables) from uint32_t to Uid_t (the one that we have implemented in c)
        // m_uid_not_relevant was added for easier use with the same function to receieve transmition from masters
        UID m_uid_from;
        UID m_uid_not_relevant; 
        char m_type;
    }__attribute__((packed));
    
    /* Master request to attach/detach minion:
    * m_uid_master: master id;
    * m_uid_minion: minion id ;
    * m_type: 'a' - attach/ 'd' - detach
    */
    struct AssigmentRequest
    {
        UID m_uid_master;
        UID m_uid_minion;
        char m_type;
    }__attribute__((packed));

    /* Master request to attach/detach minion:
    * m_uid_master: master id;
    * m_type: 'a' - attach/ 'd' - detach
    * m_status: ACK: 0x06 / NACK:0x15
    */ 
    struct AssigmentResponse
    {
        UID m_uid_minion;
        char m_type;
        char m_status;
    }__attribute__((packed));


} // namespace ilrd

#endif /* __ILRD_RD8586_MASTER_PROTOCOL_HPP__ */