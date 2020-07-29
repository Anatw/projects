/*******************************************************************************
Subject/Observer (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#ifndef ILRD_RD8586_OBSERVER_HPP
#define ILRD_RD8586_OBSERVER_HPP



class IObserver // interface class
{
public:
    virtual ~IObserver() = 0;
    virtual void Update(void *arg) = 0;
};

IObserver::~IObserver()
{
}

#endif // ILRD_RD8586_OBSERVER_HPP
