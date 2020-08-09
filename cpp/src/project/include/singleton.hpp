/*******************************************************************************
Singleton (design pattern)

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
    // return th pervious value that was inside the variable.

    if (!m_instance)
    {
        if (false ==
            (__atomic_fetch_or(&m_is_initializing, true, __ATOMIC_SEQ_CST)))
        {
            __atomic_store_n(&m_instance, new T, __ATOMIC_SEQ_CST);
            m_is_initializing = false;
        }
        // if multiple threads will enter this section, only one will enter the
        // if part and the rest will get stuck inside the else part until the
        // end of the initializaion process (when m_is_initializing will be
        // 'false' again).
        else
        {
            while (true == m_is_initializing)
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
