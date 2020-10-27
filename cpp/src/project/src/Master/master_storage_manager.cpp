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

#include "master_storage_manager.hpp"
#include "logger.hpp"

using namespace ilrd;

MasterStorageManager::MasterStorageManager(size_t num_of_minion, size_t num_of_blocks) : m_num_of_minions(num_of_minion), m_num_of_block(num_of_blocks), m_is_active(false)
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

void MasterStorageManager::ReplaceMinion()
{
    // Check if the system currently accomodating any backup minions:
    if (m_bkup_minions_list.size() > 0)
    {
        // size_t fail_minion_id = 0;
        // Iterate theough the map and check if there are any minions with "false" status - meaning minions that need to be replace - if there are - replace them:
        std::map<offset_t, minion_list_t >::iterator iterator = m_offset_map.begin();
        std::map<offset_t, minion_list_t >::iterator end = m_offset_map.end();
        minion_list_t::iterator inner_iter;
        boost::shared_ptr<MinionInfo> backup_minion;
        int offset_counter = 0;

        for (;
             iterator != end && offset_counter < m_num_offsets_per_minion;
             ++iterator)
        {
            for (inner_iter = iterator->second.begin();
                 inner_iter != iterator->second.end();
                 ++inner_iter)
            {
                if (inner_iter->get()->GetStatus() == false) // minion needs replace
                {
                    // This is the minion that needs replace:
                    // fail_minion_id = inner_iter->get()->GetId();

                    // backup_minion = m_bkup_minions_list.front();
                    // m_bkup_minions_list.pop_front();
                    
                    // iterator->second.push_back(backup_minion);

                    // ++offset_counter;

                    // break;

                    // inner_iter->get() = 
                }

                // Serch the map for the rest of the malfunctioning minion offsets:

            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::RegisterNewMinion(boost::shared_ptr<MinionInfo> minion)
{
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
        std::map< offset_t, minion_list_t >::iterator iterator;
        std::map< offset_t, minion_list_t >::iterator end = m_offset_map.end();
        int i = 0;

        for (iterator = m_offset_map.begin();
            iterator != end && i < m_num_offsets_per_minion;
            ++iterator, ++i)
        {
            if (iterator->second.size() < 2)
            {
                iterator->second.push_back(minion);
            }
        }
    }

    // check if there is a need of replace mionion and replace
    ReplaceMinion();
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
    std::map< offset_t, minion_list_t >::iterator iterator = m_offset_map.find(offset);
    minion_list_t::iterator inner_iter;
    bool data_was_lost = true;

    if (iterator != m_offset_map.end())
    { 
        for (inner_iter = iterator->second.begin(); inner_iter != iterator->second.end(); ++inner_iter)
        {
            if (inner_iter->get()->GetStatus() == true)
            {
                Request *request = BuildRequest(Request::WRITE, iterator->second.begin()->get()->GetId(), offset);

                // Insert the data into the newly created request:
                memcpy(request->m_data, data, MSG_SIZE);
                
                iterator->second.begin()->get()->Send((char *)request);
                
                data_was_lost = false;

                delete request;

                break;
            }
        }
    }
    else
    {
        LOG_ERROR(__FILE__ + std::string("::Write(): requested offset (" + offset + std::string(" has no minion connected to it")));

        throw ("No minion connected to requested offset");
    }

    if (data_was_lost)
    {
        throw (std::runtime_error("no active minion found - data lost"));
    }
}

////////////////////////////////////////////////////////////////////////////////

void MasterStorageManager::Read(size_t offset)
{
    // Find the first minion that connected to the requested offset and read data into it:
    minion_list_t::iterator inner_iter;
    std::map< offset_t, minion_list_t >::iterator iterator = m_offset_map.find(offset);
    bool data_was_lost = false;

    if (iterator != m_offset_map.end())
    {
        for (inner_iter = iterator->second.begin(); inner_iter != iterator->second.end(); ++inner_iter)
        {
            if (inner_iter->get()->GetStatus() == true)
            {
                // build the request with READ
                Request* request = BuildRequest(Request::READ, 
                    iterator->second.begin()->get()->GetId(),
                    offset);
                // Call MionionInfo Send funct
                iterator->second.begin()->get()->Send((char*)request);
                // one was found so data is not lost
                data_was_lost = false;

                delete request;

                break;
            }
        }
    }
    else
    {
        LOG_ERROR(__FILE__ + std::string("::Read(): requested offset (" + offset + std::string(" has no minion connected to it")));

        throw ("No minion connected to requested offset");
    }

    if (data_was_lost)
    {
        throw (std::runtime_error("no active minion found - data cannot be read"));
    }
}
