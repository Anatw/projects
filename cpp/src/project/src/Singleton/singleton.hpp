/*******************************************************************************
Singleton (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 29.7.20
Reviewer:
*******************************************************************************/
#ifndef __ILRD_RD8586_SINGLETON_HPP__
#define __ILRD_RD8586_SINGLETON_HPP__

#include <iostream>
#include <thread>

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
    Singleton()
    {
    }
    static T* m_instance;
    static bool m_has_instance;
};

////////////////////////////////////////////////////////////////////////////////
//                        Functions definitions:                              //
////////////////////////////////////////////////////////////////////////////////

template < typename T >
bool Singleton< T >::m_has_instance = NULL;

////////////////////////////////////////////////////////////////////////////////

template < typename T >
T* Singleton< T >::m_instance = false;

////////////////////////////////////////////////////////////////////////////////

template < class T >
T* Singleton< T >::GetInstance()
{
    if (false == __atomic_test_and_set(&m_has_instance, true))
    {
        if (NULL == m_instance)
        {
            m_instance = new T;
        }
    }

    return m_instance;
}

////////////////////////////////////////////////////////////////////////////////

template < class T >
void Singleton< T >::CleanUp()
{
    delete m_instance;
    m_has_instance = false;
}
} // namespace ilrd

#endif /* __ILRD_RD8586_SINGLETON_HPP__ */
