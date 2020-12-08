/*******************************************************************************
Dispatcher (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 26.8.20
Reviewer: Shmuel Sinder
*******************************************************************************/
#ifndef ILRD_RD8586_DISPATCHER_HPP
#define ILRD_RD8586_DISPATCHER_HPP
#include <boost/function.hpp> // boost::function
#include <iostream>           // cout
#include <list>

#include "logger.hpp"

namespace ilrd
{

// template < typename Dispatcher >
// class Callback;

////////////////////////////////////////////////////////////////////////////////
//                         Dispatcher class & functions: //
////////////////////////////////////////////////////////////////////////////////

// Subject
template < typename T >
class Dispatcher : private boost::noncopyable
{
public:
    Dispatcher()
    {
    }

    ~Dispatcher();
    typedef T dataType; // nested type

    void Subscribe(Callback< Dispatcher< T > >* callback);
    void Unsubscribe(Callback< Dispatcher< T > >* callback);
    void Notify(dataType data);

private:
    std::list< Callback< Dispatcher< T > >* > m_callback_list;
};

////////////////////////////////////////////////////////////////////////////////

template < typename T >
Dispatcher< T >::~Dispatcher()
{
    char log_msg[MSG_SIZE] = {0};

    // Removes all callback that are equals to NULL (meaning has been
    // unsubscribed from)
    m_callback_list.remove(NULL);

    typename std::list< Callback< Dispatcher< T > >* >::iterator it;
    it = m_callback_list.begin();

    while (it != m_callback_list.end())
    {
        (*it)->Unlink();
        ++it;
    }

    sprintf(log_msg, "%s: inside Dispatcher(): Unsubscribed all callbacks",
            __FILE__);
    LOG_INFO(log_msg);

    return;
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Dispatcher< T >::Subscribe(Callback< Dispatcher< T > >* callback)
{
    m_callback_list.push_front(callback);
    callback->Link(this);
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Dispatcher< T >::Unsubscribe(Callback< Dispatcher< T > >* callback)
{
    char log_msg[MSG_SIZE] = {0};

    typename std::list< Callback< Dispatcher< T > >* >::iterator it;
    it = std::find(m_callback_list.begin(), m_callback_list.end(), callback);

    if (it != m_callback_list.end())
    {
        callback->Unlink();
        // m_callback_list.erase(it);\
        // erase the CONTENT of the iterator and not the callback itself:
        *it = NULL;

        sprintf(log_msg,
                "%s: inside Unsubscribe(): Unsubscribed from callback "
                "(address: %p)",
                __FILE__, (void*)callback);
        LOG_INFO(log_msg);

        return;
    }

    sprintf(log_msg,
            "%s: inside Unsubscribe(): tried to unsubscribe a nonexisting "
            "callbacks address: %p",
            __FILE__, (void*)callback);
    LOG_WARNING(log_msg);
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Dispatcher< T >::Notify(dataType data)
{
    typename std::list< Callback< Dispatcher< T > >* >::iterator it;
    it = m_callback_list.begin();

    // Removes all callback that are equals to NULL (meaning has been
    // unsubscribed from)
    m_callback_list.remove(NULL);

    while (it != m_callback_list.end())
    {
        (*it)->Invoke(data);
        ++it;
    }

    LOG_INFO("Notify->Invoke all callback member inside callback_list\n");
}

} // namespace ilrd

#endif // ILRD_RD8586_DISPATCHER_HPP
