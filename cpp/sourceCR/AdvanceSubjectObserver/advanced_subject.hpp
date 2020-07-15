/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: 
*******************************************************************************/
#ifndef ILRD_RD8586_ADVANCED_SUBJECT_HPP
#define ILRD_RD8586_ADVANCED_SUBJECT_HPP

#include <boost/function.hpp> // boost::function
#include "iostream"           // cout

#include "advanced_observer.hpp"

typedef boost::function<void(int)> CallbackPointer;

template <typename SOURCE>
class Callback;

////////////////////////////////////////////////////////////////////////////////
//                         SimpleSrc class & functions:                          //
////////////////////////////////////////////////////////////////////////////////

// Subject
template <typename T>
class SimpleSrc : private boost::noncopyable
{
public:
    SimpleSrc() : m_callback(NULL) {}
    ~SimpleSrc();
    typedef T dataType; // nested type

    void Subscribe(Callback< SimpleSrc<T> > *callback);
    void Unsubscribe();
    void Notify(dataType data);

private:
    Callback< SimpleSrc< T > > *m_callback;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
SimpleSrc<T>::~SimpleSrc()
{
    if (m_callback)
    {
        m_callback->Unlink();
    }
}

template <typename T>
void SimpleSrc<T>::Subscribe(Callback<SimpleSrc> *callback)
{
    if (!m_callback)
    {
        m_callback = callback;
        m_callback->Link(this);
    }
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void SimpleSrc<T>::Unsubscribe()
{
    if (m_callback)
    {
        m_callback->Unlink();
        m_callback = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void SimpleSrc<T>::Notify(dataType data)
{
    if (m_callback)
    {
        m_callback->Invoke(data);
    }
}

#endif // ILRD_RD8586_ADVANCED_SUBJECT_HPP
