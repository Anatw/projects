/*******************************************************************************
Multiton is an extended form of singleton

Multiton manages multiple objects, while singleton manages just one.

1. When would you use a multiton?

2. Suggest an API and implement it

Written by Anat Wax, anatwax@gmail.com
Created: 10.8.20
*******************************************************************************/
#include <boost/noncopyable.hpp>
#include <iostream> // cout, cin, cerr
#include <vector>

using namespace std;

template < typename T, size_t size >
class Multiton : boost::noncopyable
{
public:
    T* GetInstance(int index);
    ~Multiton();

private:
    Multiton();
    vector< T* > m_instances;
};

template < typename T, size_t size >
Multiton< T, size >::Multiton()
{
}

template < typename T, size_t size >
T* Multiton< T, size >::GetInstance(int index)
{
    if (m_instances.at(index))
    {
        return (m_instances.at(index));
    }
    else
    {
        m_instances.at(index) = new T;

        return (m_instances.at(index));
    }
}

template < typename T, size_t size >
Multiton< T, size >::~Multiton()
{
    size_t i = size;
    while (i)
    {
        if (m_instances.at(i))
        {
            delete m_instances.at(i);
        }

        --i;
    }
}
