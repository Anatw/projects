#ifndef __ILRD_RD8586_MASTER_STORAGE_MANAGER_HPP__
#define __ILRD_RD8586_MASTER_STORAGE_MANAGER_HPP__
/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the final project.
This part is in charge of all the documentation and maintenance of the mapping between the offsets of the memory and the Minion responsible to operate

Authour: Anat Wax anatwax@gmail.com
Reviewer:	 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp>  // shared pointer

#include "minion_info.hpp"
#include "protocol.hpp"

namespace ilrd
{
    class MasterStorageManager : private boost::noncopyable
    {
    public:
        typedef int id_minion_t; //each minion will recive it own id
        typedef size_t offset_t; //index of data segment from the request
        typedef std::list< boost::shared_ptr<MinionInfo> > minion_list_t;

        // Say I have 4 Minions and 10 blocks, I should have 5 offsets per minion:
        //  Minions:    ||  Minion 1  |  Minion 2  |  Minion 3  |  Minion 4  |
        // Offests:     || 1,3,5,7,9  |  1,3,5,7,9 | 2,4,6,8,10 | 2,4,6,8,10 |
        // Minion 2 is a beckup on Minion 1, and Minion 4 is backup of Minion 3.
        MasterStorageManager(size_t num_of_minion, size_t num_of_blocks);
        // ~MasterStorageManager(); default

        // RegisterNewMinion
        // Recieve - A minion with its info
        // Responsible to update the m_offset_map, m_minions_list.
        void RegisterNewMinion(boost::shared_ptr< MinionInfo > minion);

        // UnregisterMinion
        // Receive - minion_id to remove
        // It will duplicate the information to the available minion.
        // Responsible to update the m_offset_map, m_minions_list.
        void UnregisterMinion(boost::shared_ptr< MinionInfo>  minion);

        //This method find the relevant minions to write to and send the data to them
        void Write(size_t offset, char *data);

        //This method find the minion to read from and return the data.
        void Read(size_t offset);

        bool ShouldAddMinion();

    private:
        // map of pairs of minions that store the related offsets (key) and minion_list_t (value). Every offset in the map contain a list of two minions (for raid1)
        std::map< offset_t, minion_list_t > m_offset_map;

        // m_minions_list is a list of all active minions in our system:
        minion_list_t m_minions_list;
        // m_bkup_minions_list is a list of minions that when they were added to our system, the sytem already had m_num_of_minions in it. The minions in this list will wait for when the system will need a minion to backup another minion:
        minion_list_t m_bkup_minions_list;

        size_t m_num_of_minions;
        size_t m_num_of_block;
        int m_num_offsets_per_minion; // problematic logic. should be deleted
        bool m_is_active;
        // m_offset will represent the current offset the next Minion shuold be assigned to:
        size_t m_offset;
        char m_num_minions_per_offset; // This will be equal to 2 - because of RAID01
        // This condition will be chacked (using the ShouldAddMinion() method) every time a broadcast response from a Minion that is not inside the UDPcommunicator list of minions will arrive.
        bool m_add_new_minion;


        void InitMap();
        // void ReplaceMinion();

        static Request *BuildRequest(Request::MODE mode, uint64_t uid, uint64_t index);
    };
} // namespace ilrd

#endif /* __ILRD_RD8586_MASTER_STORAGE_MANAGER_HPP__ */