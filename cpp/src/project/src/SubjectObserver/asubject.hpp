/*******************************************************************************
Subject/Observer (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#ifndef ILRD_RD8586_SUBJECT_HPP
#define ILRD_RD8586_SUBJECT_HPP

#include <algorithm> // find()
#include <iostream>
#include <string>
#include <vector>

#include "iobserver.hpp"

using namespace std;

// The Subject owns some important state and notifies observers when the state
// changes.
class ASubject // abstract class
{
public:
    virtual ~ASubject() = 0;
    void Attach(IObserver* observer);
    void Detach(IObserver* observer);

protected:
    void Notify();

private:
    vector< IObserver* > m_observers_list;
};

////////////////////////////////////////////////////////////////////////////////
//                            Inline functions:                               //
////////////////////////////////////////////////////////////////////////////////

ASubject::~ASubject()
{
}

void ASubject::Attach(IObserver* observer)
{
    m_observers_list.push_back(observer);
}

void ASubject::Detach(IObserver* observer)
{
    vector< IObserver* >::iterator it;
    it = find(m_observers_list.begin(), m_observers_list.end(), observer);
    if (it != m_observers_list.end())
    {
        m_observers_list.erase(it);
    }
}

void ASubject::Notify()
{
    for (size_t i = 0; i < m_observers_list.size(); ++i)
    {
        m_observers_list[i]->Update(NULL);
    }
}

#endif // ILRD_RD8586_SUBJECT_HPP
