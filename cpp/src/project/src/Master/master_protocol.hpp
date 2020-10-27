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

namespace ilrd
{
    /*Master request :
    * m_uid_from: own id;
    * m_type: 'b' - broadcast;
    
    * Minion answer :
    * m_uid_from: own id;
    * m_type: 'b' - broadcast;
    */
    // The master will send this request - this is the broadcast that will be sent to the entire system.
    // The minion will answer to this request if he either - not connected to any master/ connected to the master that sent the broadcast.
    typedef struct BroadcastFrom
    {
        uint32_t m_uid_from;
        char m_type;
    }__attribute__((packed));
    
    /* Master request to attach/detach minion:
    * m_uid_master: master id;
    * m_uid_minion: minion id ;
    * m_type: 'a' - attach/ 'd' - detach
    */
    struct AssigmentRequest
    {
        uint32_t m_uid_master;
        uint32_t m_uid_minion;
        char m_type;
    }__attribute__((packed));

    /* Master request to attach/detach minion:
    * m_uid_master: master id;
    * m_type: 'a' - attach/ 'd' - detach
    * m_status: ACK: 0x06 / NACK:0x15
    */ 
    struct AssigmentResponse
    {
        uint32_t m_uid_minion;
        char m_type;
        char m_status;
    }__attribute__((packed));


} // namespace ilrd

#endif /* __ILRD_RD8586_MASTER_PROTOCOL_HPP__ */