/*******************************************************************************
Dispatcher (design pattern)

Written by Anat Wax, anatwax@gmail.com
Created: 26.8.20
Reviewer: Shmuel Sinder
*******************************************************************************/
#include <boost/bind.hpp>
#include <iostream> // cout, cin, cerr

#include "dispatcher.hpp"
#include "dispatcher_callback.hpp"

using namespace ilrd;

class Button : public Dispatcher< int >
{
public:
    void Press()
    {
        int a = 2;
        Notify(a);
    }
};

void Update(int num)
{
    std::cout << "\nbutton pressed and doing something..." << num << std::endl;
}

// class DoSomething : public Callback< Button >
// {
// public:
//     // DoSomething() : Callback< Button >(boost::bind(Update, this, _1))
//     // {
//     // }

// };

int main()
{
    // Dispatcher< int > dispatcher;
    // Callback< Dispatcher< int > > callback(Update);

    // dispatcher.Subscribe(&callback);

    // dispatcher.Notify(79);

    Button button;
    Dispatcher< int > dispatcher;
    Callback< Dispatcher< int > >::CallbackPointer callback(Update);
    Callback< Dispatcher< int > >* this_callback =
        new (Callback< Dispatcher< int > >)(callback);

    // dispatcher.Subscribe(this_callback);
    dispatcher.Notify(79);

    button.Subscribe(this_callback);
    std::cout << "\nThe button is beeing pressed:" << std::endl;
    button.Press();

    button.Unsubscribe(this_callback);
    std::cout << "\nThe button is beeing pressed:" << std::endl;
    button.Press();

    delete this_callback;

    return (0);
}
