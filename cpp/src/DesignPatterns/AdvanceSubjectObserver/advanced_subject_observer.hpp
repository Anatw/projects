/*******************************************************************************

Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: 
*******************************************************************************/
#ifndef ILRD_RD8586_ADVANCED_SUBJECT_OBSERVER_HPP
#define ILRD_RD8586_ADVANCED_SUBJECT_OBSERVER_HPP

#include <boost/function.hpp> // boost::function
#include "iostream" // cout

typedef boost::function<void(int)>CallbackPointer;

template < typename SOURCE >
class Callback;

////////////////////////////////////////////////////////////////////////////////
//                         Source class & functions:                          //
////////////////////////////////////////////////////////////////////////////////

// Subject
template < typename T >
class Source : private boost::noncopyable
{
public:
    Source() {}
    ~Source() {}
    typedef T dataType; // nested type

    void Subscribe(Callback<Source> *callback);
    void Unsubscribe();
    virtual void Notify(dataType data);

private:
    Callback< Source >* m_callback;
};

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Source<T>::Subscribe(Callback<Source> *callback)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Source<T>::Unsubscribe()
{
    m_callback = NULL;
}

////////////////////////////////////////////////////////////////////////////////

template < typename T >
void Source<T>::Notify(dataType data)
{
    std::cout << "Notify" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//                        Callback class & functions:                         //
////////////////////////////////////////////////////////////////////////////////


namespace detail
{
void EmptyFunction()
{
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
    Callback(const CallbackPointer& func,
             const DeathPointer& death_func = detail::EmptyFunction)
             : m_func(func), m_death_func(death_func) {}

    inline ~Callback()
    {
        Unlink(m_source);
    };

    // should move to the private section
    void Link(SOURCE* source);
    void Unlink(SOURCE* source);
    void Invoke(typename SOURCE::dataType data);
    // friend SOURCE;

private:
    SOURCE* m_source;
    const CallbackPointer& m_func;
    const DeathPointer& m_death_func;
};
template < typename SOURCE >
class Callback;

////////////////////////////////////////////////////////////////////////////////


template < typename SOURCE >
void Callback<SOURCE>::Link(SOURCE* source)
{
    m_source = source;
    m_source->Subscribe(this);
}

////////////////////////////////////////////////////////////////////////////////


template < typename SOURCE >
void Callback<SOURCE>::Unlink(SOURCE* source)
{
    m_source->Unsubscribe();
    m_source = NULL;
}

////////////////////////////////////////////////////////////////////////////////


template < typename SOURCE >
void Callback<SOURCE>::Invoke(typename SOURCE::dataType data)
{
    m_source->Notify(data);
}

#endif // ILRD_RD8586_ADVANCED_SUBJECT_OBSERVER_HPP
