/*******************************************************************************
Written by Anat Wax, anatwax@gmail.com
Created: 16.7.20
Reviewer: Ivanna Fleisher
*******************************************************************************/
#ifndef ILRD_RD8586_ADVANCED_OBSERVER_HPP
#define ILRD_RD8586_ADVANCED_OBSERVER_HPP

#include <boost/function.hpp> // boost::function
#include <boost/noncopyable.hpp>
#include <cassert>            // assert
#include <iostream>           // cout


#define LOG_ERR(X) (std::cerr << "ERROR: " << (X) << std::endl)
#define LOG_WRN(X) (std::cerr << "WARNING: " << (X) << std::endl)

typedef boost::function< void(int) > CallbackPointer;

////////////////////////////////////////////////////////////////////////////////
//                        Callback class & functions:                         //
////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    inline void EmptyFunction()
    {
        std::cout << "default EmpthyFunctions() was called" << std::endl;
    }
} // namespace detail

// observer
template < typename SOURCE >
class Callback : private boost::noncopyable
{
public:
    // What should the subject do when a notification is signaled
    typedef boost::function< void(typename SOURCE::dataType) > CallbackPointer;
    typedef boost::function< void() > DeathPointer;

    Callback(CallbackPointer func,
             DeathPointer death_func = detail::EmptyFunction)
        : m_source(NULL), m_func(func), m_death_func(death_func)
    {
    }

    inline ~Callback();

private: // for the friend
    struct FriendHelper
    {
        typedef SOURCE MySource;
    };
    friend struct FriendHelper::MySource;

    void Link(SOURCE* source);
    void Unlink(bool should_notify = false);
    void Invoke(typename SOURCE::dataType data);
    void InvokeDeath();

private: // class private
    SOURCE* m_source;
    const CallbackPointer m_func;
    DeathPointer m_death_func;
};

////////////////////////////////////////////////////////////////////////////////

template < typename SOURCE >
Callback< SOURCE >::~Callback()
{
    if (m_source)
    {
        m_source->Unsubscribe(this);
    }
}

////////////////////////////////////////////////////////////////////////////////

template < typename SOURCE >
void Callback< SOURCE >::Link(SOURCE* source)
{
    assert(!m_source);
    assert(source);

    m_source = source;
}

////////////////////////////////////////////////////////////////////////////////

template < typename SOURCE >
void Callback< SOURCE >::Unlink(bool should_notify)
{
    assert(m_source);

    if (should_notify)
    {
        std::cout << "a source " << m_source << " has been unsubscribed\n"
                  << std::endl;
    }

    m_source = NULL;
}

////////////////////////////////////////////////////////////////////////////////

// template <typename dataType>
template < typename SOURCE >
void Callback< SOURCE >::Invoke(typename SOURCE::dataType data)
{
    assert(m_source);
    assert(m_func);

    m_func(data);
}

#endif // ILRD_RD8586_ADVANCED_OBSERVER_HPP
