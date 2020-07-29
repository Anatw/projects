/*******************************************************************************
Scheduler (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 21.7.20
Reviewer: Kobi Rappaport
*******************************************************************************/
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <iostream> // cout, cin, cerr

#include "scheduler.hpp"

using namespace std;
using namespace ilrd;

Scheduler::Scheduler(Reactor& reactor)
try : m_timer(reactor, boost::bind(&Scheduler::ActivateNextTask, this,
                                   _1)) //-1 is a placeholder that will pass on
                                        // what the funtion receieves
{
}
catch (...)
{
    throw runtime_error("Error in scheduler constructor");
}

////////////////////////////////////////////////////////////////////////////////

Scheduler::~Scheduler()
{
}

////////////////////////////////////////////////////////////////////////////////

void Scheduler::ScheduleAction(TimePoint timepoint, ActionFunc function)
{
    Scheduler::Task new_task;
    new_task.m_function = function;
    new_task.m_timepoint = timepoint;

    m_tasks.push(new_task);

    // If the new task should begin before the current first task
    // in the queue - if so - i need to activate timer set
    if (new_task.m_timepoint == m_tasks.top().m_timepoint)
    {
        // This will return in nano-seconds, and
        // it needs to cast it in microseconds.
        MS time = boost::chrono::duration_cast< MS >(new_task.m_timepoint -
                                                     this->Now());
        m_timer.Set(time);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Scheduler::ScheduleAction(MS microseconds, ActionFunc function)
{
    TimePoint time_point = TimePoint(microseconds + Now());

    ScheduleAction(time_point, function);
}

////////////////////////////////////////////////////////////////////////////////

Scheduler::TimePoint Scheduler::Now()
{
    return (boost::chrono::system_clock::now());
}

////////////////////////////////////////////////////////////////////////////////

void Scheduler::ActivateNextTask(int fd)
{
    assert(!m_tasks.empty());

    // remove the first task in queue
    Scheduler::Task task_to_execute = m_tasks.top();
    m_tasks.pop();

    // activate the task
    task_to_execute.m_function(fd);

    if (m_tasks.empty())
    {
        m_timer.Unset();

        return;
    }

    // activate timer with the next task in line
    MS time = boost::chrono::duration_cast< MS >(m_tasks.top().m_timepoint -
                                                 this->Now());
    m_timer.Set(time);
}
