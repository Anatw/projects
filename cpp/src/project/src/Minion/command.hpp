/*******************************************************************************
base_command (part of the Minion final project)

The essense of this class is to cancel the if statements inside the Minion
class, in the OnRequest() method. The factory will create, on runtime, the
correct read/writre request.

Written by Anat Wax, anatwax@gmail.com
Created: 19.8.20
Reviewer: Daria Korotkova
*******************************************************************************/

#ifndef __ILRD_RD8586_COMMAND_HPP_
#define __ILRD_RD8586_COMMAND_HPP_

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "protocol.hpp"
#include "storage.hpp"

namespace ilrd
{

class BaseCommand
{
public:
    virtual ~BaseCommand()
    {
    }

    virtual void operator()() = 0;
};

class Params
{
public:
    Params(Storage< MAX_BLOCK_SIZE >& storage, Response& response,
           const Request& request)
        : m_storage(storage), m_response(response), m_request(request)
    {
    }

    Storage< MAX_BLOCK_SIZE >& m_storage;
    Response& m_response;
    const Request& m_request;
};

class WriteCommand : public BaseCommand
{
public:
    WriteCommand(Params params) : m_params(params)
    {
    }

    void operator()();

private:
    Params m_params;
};

class ReadCommand : public BaseCommand
{
public:
    ReadCommand(Params params) : m_params(params)
    {
    }

    void operator()();

private:
    Params m_params;
};

// BUILDERS

BaseCommand* WriteBuilder(Params m_params);
BaseCommand* ReadBuilder(Params m_params);
} // namespace ilrd

#endif /* __ILRD_RD8586_COMMAND_HPP_ */
