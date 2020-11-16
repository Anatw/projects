/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax anatwax@gmail.com
Reviewer: 
Creation date: 20.09.2020
Version: 2 (5.11.20)
*******************************************************************************/

#include "master_storage_manager.hpp"
#include "logger.hpp"

using namespace ilrd;

MasterStorageManager::MasterStorageManager(size_t num_of_minion, size_t num_of_blocks) : m_num_of_minions(num_of_minion), m_num_of_block(num_of_blocks), m_is_active(false), m_offset(0), m_num_minions_per_offset(2)
{
    m_num_offsets_per_minion = m_num_of_block / (m_num_of_minions / 2);

    InitMap();
}

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::MasterStorageManager::InitMap()
{
    // Iterate the map and insert the amount of m_num_of_blocks as keys, with a minion_list_t for each index (at first the list will be empty - when a Minion regiester to the system it will be added to the list):
    minion_list_t *inner_value_indexs = new minion_list_t[m_num_of_block];
    for (size_t i = 0; i < m_num_of_block; ++i)
    {
        m_offset_map.insert(std::make_pair(i, inner_value_indexs[i]));
    }    
}

////////////////////////////////////////////////////////////////////////////////

// void MasterStorageManager::ReplaceMinion()
// {
//     // Check if the system currently accomodating any backup minions:
//     if (m_bkup_minions_list.size() > 0)
//     {
        // If there are minion's in backup list - send them an attach request:
        

        // size_t fail_minion_id = 0;
        // Iterate theough the map and check if there are any minions with "false" status - meaning minions that need to be replace - if there are - replace them:
        // std::map<offset_t, minion_list_t >::iterator iterator = m_offset_map.begin();
        // std::map<offset_t, minion_list_t >::iterator end = m_offset_map.end();
        // minion_list_t::iterator inner_iter;
        // boost::shared_ptr<MinionInfo> backup_minion;
        // int offset_counter = 0;

        // for (; // the logic of m_num_offsets_per_minion is problematic - should be replaced and deleted
        //      iterator != end && offset_counter < m_num_offsets_per_minion;
        //      ++iterator)
        // {
        //     for (inner_iter = iterator->second.begin();
        //          inner_iter != iterator->second.end();
        //          ++inner_iter)
        //     {
    //     //         if (inner_iter->get()->GetStatus() == false) // minion needs replace
    //             {
    //                 // This is the minion that needs replace:
    //                 // fail_minion_id = inner_iter->get()->GetId();

    //                 // backup_minion = m_bkup_minions_list.front();
    //                 // m_bkup_minions_list.pop_front();
                    
    //                 // iterator->second.push_back(backup_minion);

    //                 // ++offset_counter;

    //                 // break;

    //                 // inner_iter->get() = 
    //             }

    //             // Serch the map for the rest of the malfunctioning minion offsets:

    //         }
    //     }
    // }
// }

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::RegisterNewMinion(boost::shared_ptr<MinionInfo> minion)
{
    // I receieved a minion. I need to check if it is in my map and 
    bool add_to_map = false;
    // If more minion can be active in the system - they should be added to the list of active minion. If not - they will be added to the list of backup minions:
    if (m_minions_list.size() < m_num_of_minions)
    {
        m_minions_list.push_back(minion);
        add_to_map = true;
    }
    else
    {
        m_bkup_minions_list.push_back(minion);
    }

    // look inside the m_offset_map and see to which offset need a storing minion/backup minion (meaning that the value list in that offset index has less than two minions). Add it there.
    if (add_to_map)
    {
        for (size_t i = 0; i < m_num_of_block; ++i)
        {
            if (m_offset == i % (m_num_of_minions / 2))
            {
                m_offset_map[i].push_back(minion);
            }
        }
        
        // set m_offset to the next offset - ready for the next Minion to register:
        m_offset = (m_offset + 1) % (m_num_of_minions / 2);
    }

    // // check if there is a need of replace mionion and replace
    // ReplaceMinion();
}

////////////////////////////////////////////////////////////////////////////////

bool MasterStorageManager::ShouldAddMinion()
{
    if (m_num_of_minions == m_minions_list.size())
    {
        return false;
    }
    else
    {
        return true;
    }
    
}
////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::UnregisterMinion(boost::shared_ptr<MinionInfo> minion)
{
    std::map< offset_t, minion_list_t >::iterator iterator;
    std::map< offset_t, minion_list_t >::iterator end = m_offset_map.end();

    for (iterator = m_offset_map.begin(); iterator != end; ++iterator)
    {
        iterator->second.remove(minion);
    }

    m_minions_list.remove(minion);

    m_add_new_minion = true;

    // check if there is a need of replace mionion and replace
    // ReplaceMinion();
}

////////////////////////////////////////////////////////////////////////////////

Request* MasterStorageManager::BuildRequest(Request::MODE mode, uint64_t id, uint64_t offset)
{
    Request *request = 
                    (Request*)operator new(MSG_SIZE + Request().RequestSize());

    request->m_mode = mode;
    request->m_uid = id;
    request->m_index = offset;

    return request;
}

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::Write(size_t offset, char *data)
{
    // Find the first minion that connected to the requested offset and insert data into it:
    minion_list_t minion_list = m_offset_map[offset];
    minion_list_t::iterator iterator = minion_list.begin();
    bool data_was_lost = false;

    if (minion_list.size() == 0)
    {
        LOG_ERROR(__FILE__ + std::string("::Read(): requested offset (" + offset + std::string(" has no minion connected to it")));

        // throw ("No minion connected to requested offset");
    }

    for (size_t i = 0; i < m_num_of_minions; ++i)
    {
        if (iterator->get()->GetStatus() == true) // If minion is active
        {
            Request *request = BuildRequest(Request::WRITE, iterator->get()->GetId(), offset);

            // Insert the data into the newly created request:
            memcpy(request->m_data, data, MSG_SIZE);
            
            iterator->get()->Send((char *)request);
            
            data_was_lost = false;

            delete request;

            break;
        }

        ++iterator;
    }

    if (data_was_lost)
    {
        throw (std::runtime_error("no active minion found - data cannot be read"));
    }
}

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::Read(size_t offset)
{
    // Find the first minion that connected to the requested offset and read data into it:
    minion_list_t minion_list = m_offset_map[offset];
    minion_list_t::iterator iterator = minion_list.begin();
    bool data_was_lost = false;

    if (minion_list.size() == 0)
    {
        LOG_ERROR(__FILE__ + std::string("::Read(): requested offset (" + offset + std::string(" has no minion connected to it")));

        // throw ("No minion connected to requested offset");
    }

    for (size_t i = 0; i < m_num_of_minions; ++i)
    {
        if (iterator->get()->GetStatus() == true) // If minion is active
        {
            // build the request with READ
            Request* request = BuildRequest(Request::READ, iterator->get()      ->GetId(), offset);
            // Call MionionInfo Send funct
            iterator->get()->Send((char*)request);
            // one was found so data is not lost
            data_was_lost = false;

            delete request;

            break;
        }

        ++iterator;
    }

    if (data_was_lost)
    {
        throw (std::runtime_error("no active minion found - data cannot be read"));
    }
}
