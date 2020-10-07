/*******************************************************************************
base_command (part of the Minion final project)

The essense of this class is to cancle the if statements inside the Minion
class, in the OnRequest() method. The factory will create, on runtime, the
correct

Written by Anat Wax, anatwax@gmail.com
Created: 19.8.20
Reviewer: Daria Korotkova
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "command.hpp"

using namespace ilrd;

void ReadCommand::operator()()
{
    try
    {
        m_params.m_storage.Read((m_params.m_request.m_index),
                                m_params.m_response.m_data);
    }
    catch (...)
    {
        m_params.m_response.m_status = 1;

        LOG_ERROR(__FILE__ +
                  std::string("::ReadRequest(): error in Read() method"));

        throw std::runtime_error("error in Read() method");
    }
}

void WriteCommand::operator()()
{
    try
    {
        m_params.m_storage.Write((m_params.m_request.m_index),
                                 m_params.m_request.m_data);
    }
    catch (...)
    {
        m_params.m_response.m_status = 1;

        LOG_ERROR(__FILE__ +
                  std::string("::ReadRequest(): error in Write() method"));

        throw std::runtime_error("error in Write() method");
    }
}

BaseCommand* ilrd::ReadBuilder(Params m_params)
{
    return (new ReadCommand(m_params));
}

BaseCommand* ilrd::WriteBuilder(Params m_params)
{
    return (new WriteCommand(m_params));
}
