/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: 
*******************************************************************************/
#ifndef ILRD_RD8586_ADVANCED_OBSERVER_HPP
#define ILRD_RD8586_ADVANCED_OBSERVER_HPP

#include <boost/function.hpp> // boost::function
#include <iostream>           // cout

typedef boost::function<void(int)> CallbackPointer;

////////////////////////////////////////////////////////////////////////////////
//                        Callback class & functions:                         //
////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    void EmptyFunction()
    {
        std::cout << "default EmpthFunctions() was called" << std::endl;
    }

} // namespace detail

// observer
template <typename SOURCE>
class Callback : private boost::noncopyable
{
public:
    // What should the subject do when a notification is signaled
    typedef boost::function<void(typename SOURCE::dataType)> CallbackPointer;
    typedef boost::function<void()> DeathPointer;

    Callback(CallbackPointer func,
             DeathPointer death_func = detail::EmptyFunction);

    inline ~Callback()
    {
        m_source->Unsubscribe();
    }

    void InitializeFuncs();

    // should move to the private section
    void Link(SOURCE *source);
    void Unlink();
    void Invoke(typename SOURCE::dataType data);
    void InvokeDeath();
    // friend SOURCE;

private:
    SOURCE *m_source;
    CallbackPointer m_func;
    DeathPointer m_death_func;
};

////////////////////////////////////////////////////////////////////////////////

void InitializeFuncs()
{
}

typedef boost::function<void(typename SOURCE::dataType)> CallbackPointer() typedef boost::function<void()> DeathPointer;

template <typename SOURCE>
Callback<SOURCE>::Callback(CallbackPointer func,
                           DeathPointer death_func = detail::EmptyFunction)
    : m_source(NULL)
{
    InitializeFuncs();
}

template <typename SOURCE>
void Callback<SOURCE>::Link(SOURCE *source)
{
    m_source = source;
}

////////////////////////////////////////////////////////////////////////////////

template <typename SOURCE>
void Callback<SOURCE>::Unlink()
{
    if (m_source)
    {
        m_source = NULL;
        m_death_func();
    }
    else
    {
    }
}

////////////////////////////////////////////////////////////////////////////////

// template <typename dataType>
template <typename SOURCE>
void Callback<SOURCE>::Invoke(typename SOURCE::dataType data)
{
    if (m_func)
    {
        m_func(data);
    }
    else
    {
        //warning
    }
}

#endif // ILRD_RD8586_ADVANCED_OBSERVER_HPP
