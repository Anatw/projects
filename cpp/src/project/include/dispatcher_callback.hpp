/*******************************************************************************
Dispatcher (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 26.8.20
Reviewer: Shmuel Sinder
*******************************************************************************/
#ifndef ILRD_RD8586_DISPATCHER_CALLBACK_HPP
#define ILRD_RD8586_DISPATCHER_CALLBACK_HPP

#include <boost/function.hpp> // boost::function
#include <boost/noncopyable.hpp>
#include <iostream> // cout
#include <list>

#include "logger.hpp"

namespace ilrd
{

namespace detail
{
inline void EmptyFunction()
{
    std::cout << "default EmpthFunctions() was called" << std::endl;
}
} // namespace detail
////////////////////////////////////////////////////////////////////////////////
//                         Callback class & functions: //
////////////////////////////////////////////////////////////////////////////////

template < typename DISPATCHER >
class Callback : private boost::noncopyable
{
public:
    typedef boost::function< void(typename DISPATCHER::dataType) >
        CallbackPointer;
    typedef boost::function< void() > DeathPointer;

    Callback(const CallbackPointer& callback_func,
             const DeathPointer& death_func = &detail::EmptyFunction)
        : m_callback_func(callback_func), m_death_func(death_func)
    {
    }

    ~Callback();

private:
    void Link(DISPATCHER* dispatcher);
    void Unlink();
    void Invoke(typename DISPATCHER::dataType data);

    CallbackPointer m_callback_func;
    DeathPointer m_death_func;

    DISPATCHER* m_dispatcher;

    struct FriendHelper
    {
        typedef DISPATCHER MyDispatcher;
    };
    friend class FriendHelper::MyDispatcher;
};

////////////////////////////////////////////////////////////////////////////////

template < typename DISPATCHER >
Callback< DISPATCHER >::~Callback()
{
    if (m_dispatcher)
    {
        m_dispatcher->Unsubscribe(this);
    }

    if (m_death_func)
    {
        m_death_func();
    }
}

////////////////////////////////////////////////////////////////////////////////

template < typename DISPATCHER >
void Callback< DISPATCHER >::Link(DISPATCHER* dispatcher)
{
    assert(dispatcher);

    m_dispatcher = dispatcher;
}

////////////////////////////////////////////////////////////////////////////////

template < typename DISPATCHER >
void Callback< DISPATCHER >::Unlink()
{
    char log_msg[MSG_SIZE] = {0};

    // add a chack if I'm trying to unsubscribed something that is already
    // unsubscribed - throw. add in the API that this function is throwable
    if (!m_dispatcher)
    {
        sprintf(log_msg,
                "%s: inside Unlink(): unable to unlink address %p - "
                "m_dispathcer is NULL",
                __FILE__, (void*)this->m_dispatcher);
        LOG_ERROR(log_msg);

        throw std::runtime_error("can't Unlink - m_dispatcher is NULL\n");
    }

    sprintf(log_msg,
            "%s: inside Unlink(): a source (m_dispatcher address %p) has been "
            "unsubscribed\n",
            __FILE__, (void*)m_dispatcher);
    LOG_ERROR(log_msg);

    m_dispatcher = NULL;
}

////////////////////////////////////////////////////////////////////////////////

// template <typename dataType>
template < typename DISPATCHER >
void Callback< DISPATCHER >::Invoke(typename DISPATCHER::dataType data)
{
    assert(m_dispatcher);
    assert(m_callback_func);

    m_callback_func(data);
}

} // namespace ilrd

#endif // ILRD_RD8586_DISPATCHER_CALLBACK_HPP
