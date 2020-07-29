/*******************************************************************************
The Subject/Observer design pattern allow to make manipulations on the Subject
and the Observer independently from each other.
The Observer Pattern defines a one-to-many dependency between objects so that
when one object changes state, all of its dependents are notified and updated
automatically.


Subject/Observer (design pattern)
Written by Anat Wax, anatwax@gmail.com
Created: 9.7.20
Reviewer: Haim Sa'adia
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <vector>

#include "asubject.hpp"

using namespace std;

class Button : public ASubject
{
    public:
    void Press()
    {
        Notify();
    }
};

class DoSomething : public IObserver
{
    public:
    void Update(void *arg)
    {
        cout << "\nbutton pressed and doing something..." << arg << endl;
    }
};

int main()
{
    Button button;
    DoSomething action;
    
    button.Attach(&action);
    cout << "\nThe button is beeing pressed:" << endl;
    button.Press();

    button.Detach(&action);
    cout << "\nThe button is beeing pressed:" << endl;
    button.Press();

    return (0);
}
