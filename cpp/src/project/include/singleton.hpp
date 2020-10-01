/*******************************************************************************
Singleton (design pattern) - thread safe

Written by Anat Wax, anatwax@gmail.com
Created: 29.7.20
Reviewer: Lior Cohen
*******************************************************************************/
#ifndef __ILRD_RD8586_SINGLETON_HPP__
#define __ILRD_RD8586_SINGLETON_HPP__

#include <assert.h>
// #include <atomic> // atomic bool
#include <iostream>
#include <pthread.h>

#include "boost/core/noncopyable.hpp"

namespace ilrd
{

////////////////////////////////////////////////////////////////////////////////
//                           Class declaration:                               //
////////////////////////////////////////////////////////////////////////////////

// The GetInstance method must be static - because the constructor is private,
// the only way to create a singleton is with a method that is not connected to
// a specific clase, hence - a static method, which is a global method, that the
// user can call to using the class'es namespace
//(inside the main:
// T t = Singleton< T >::GetInstance();)
// and because GetInstance is statis and static functions can touch only static
// varibles, the variables inside the singleton class must also be static.

template < class T >
class Singleton : private boost::noncopyable
{
public:
    inline static T* GetInstance();
    static void CleanUp();

private:
    Singleton();

    static T* m_instance;
    static int m_is_initializing;
};

////////////////////////////////////////////////////////////////////////////////
//                        Functions definitions:                              //
////////////////////////////////////////////////////////////////////////////////

template < typename T >
T* Singleton< T >::m_instance = NULL;

template < typename T >
int Singleton< T >::m_is_initializing = false;

////////////////////////////////////////////////////////////////////////////////

template < class T >
T* Singleton< T >::GetInstance()
{
    // the "__atomic_fetch_or" will set the value using OR opperation and will
    // return the pervious value that was inside the variable.

    if (!m_instance)
    {
        // This will change the value inside m_is_initializing to true, and will
        // check if it was priviously "false":
        if (false ==
            (__atomic_fetch_or(&m_is_initializing, true, __ATOMIC_SEQ_CST)))
        {
            __atomic_store_n(&m_instance, new T, __ATOMIC_SEQ_CST);
            atexit(Singleton::CleanUp);
            __atomic_fetch_and(&m_is_initializing, false, __ATOMIC_SEQ_CST);
        }
        // if multiple threads will enter this section, only one will enter the
        // if part and the rest will get stuck inside the else part until the
        // end of the initializaion process (when m_is_initializing will be
        // 'false' again).
        else
        {
            // "__atomic_fetch_and" will check if the variable
            // (m_is_initializing) has the value specified (true)
            while (
                __atomic_fetch_and(&m_is_initializing, true, __ATOMIC_SEQ_CST))
            {
                ; // spinlock...
            }
        }
    }

    assert(m_instance);

    return m_instance;
}

////////////////////////////////////////////////////////////////////////////////

template < class T >
void Singleton< T >::CleanUp()
{
    delete m_instance;
    m_instance = NULL;
    m_is_initializing = false;
}

} // namespace ilrd

#endif /* __ILRD_RD8586_SINGLETON_HPP__ */
