/*******************************************************************************
Written by Anat Wax, anatwax@gmail.com
Created: 16.7.20
Reviewer: Ivanna Fleisher
*******************************************************************************/
#ifndef ILRD_RD8586_ADVANCED_SUBJECT_HPP
#define ILRD_RD8586_ADVANCED_SUBJECT_HPP

#include "iostream"           // cout
#include <boost/function.hpp> // boost::function

#define LOG_ERR(X) (std::cerr << "ERROR: " << (X) << std::endl)
#define LOG_WRN(X) (std::cerr << "WARNING: " << (X) << std::endl)

template < typename SOURCE >
class Callback;

////////////////////////////////////////////////////////////////////////////////
//                         SimpleSrc class & functions:                       //
////////////////////////////////////////////////////////////////////////////////

// Subject
template < typename T >
class SimpleSrc : private boost::noncopyable
{
public:
    SimpleSrc() : m_callback(NULL)
    {
    }
    ~SimpleSrc();
    typedef T dataType; // nested type

    void Subscribe(Callback< SimpleSrc< T > >* callback);
    void Unsubscribe(Callback< SimpleSrc< T > >* callback);
    void Notify(dataType data);

private:
    Callback< SimpleSrc< T > >* m_callback;
};

////////////////////////////////////////////////////////////////////////////////

template < typename T >
SimpleSrc< T >::~SimpleSrc()
{
    if (m_callback)
    {
        m_callback->Unlink(true);
    }
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void SimpleSrc< T >::Subscribe(Callback< SimpleSrc< T > >* callback)
{
    assert(callback);
    assert(!m_callback);

    m_callback = callback;
    m_callback->Link(this);
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void SimpleSrc< T >::Unsubscribe(Callback< SimpleSrc< T > >* callback)
{
    assert(m_callback ==
           callback); // make sure we are trying to unsubscribe from a place you
                      // are already subscribed to.
    if (!callback)
    {
        LOG_ERR("in Unsubscribe() - empty callback pointer");
    }

    if (m_callback == callback) // Unsubscribing from the correct service
    {
        m_callback->Unlink(false);
        m_callback = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void SimpleSrc< T >::Notify(dataType data)
{
    if (m_callback)
    {
        m_callback->Invoke(data);
    }
    else
    {
        LOG_WRN("Notify->Invoke was called with no callback member inside the "
                "subject\n");
    }
}

#endif // ILRD_RD8586_ADVANCED_SUBJECT_HPP
