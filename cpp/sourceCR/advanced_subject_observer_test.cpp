/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <cassert>

#include "advanced_subject.hpp"

using namespace std;
// using namespace ilrd;


class SubjectThermoExample;

void TempHandler(int num)
{
    if (num > 5)
    {
        cout << "temp is " << num << ", cooling myself!" << endl;
    }
    else if (num < 0)
    {
        cout << "temp is " << num << ", stop cooling myself!" << endl;
    }
    else
    {
        cout << "temp is " << num << ", we are just fine!" << endl;
    }
}

void ReportThermometerDied()
{
    cout << "Thermometer won't send more date to fridge" << endl;
}

class SubjectThermoExample
{
public:
    typedef Callback< Source< int > > MyCallback;
    void WatchTemp(MyCallback* callback)
    {
        src.Subscribe(callback);
    }

    void ChangeInTemp(int temp)
    {
        src.Notify(temp);
    }

private:
    Source< int > src;
};

class ObserverFridgeExample
{
public:
    ObserverFridgeExample(
        Callback< Source< int > >::CallbackPointer callback = TempHandler)
        : m_callback(callback, ReportThermometerDied)
    {
    }
    void WatchTemp(SubjectThermoExample& thermo)
    {
        thermo.WatchTemp(&m_callback);
    }

private:
    Callback< Source< int > > m_callback;
};

void BasicTests();

int main()
{
    BasicTests();
    return (0);
}

void BasicTests()
{
    ObserverFridgeExample* fridge = new ObserverFridgeExample(TempHandler);
    SubjectThermoExample* thermometer = new SubjectThermoExample;

    fridge->WatchTemp(*thermometer);

    thermometer->ChangeInTemp(3);
    thermometer->ChangeInTemp(7);
    thermometer->ChangeInTemp(2);
    thermometer->ChangeInTemp(-3);
    // delete thermometer;
    delete fridge;
    thermometer->ChangeInTemp(-3);
}


// class Fridge : private Callback<Fridge>
// {
//     public:
//     Fridge(Callback<Source<int>>::CallbackPointer callback = CallBackPTR) : m_call

//     private:
    
// };

// class Thermometer : private Source<float>
// {
// public:
//     typedef Callback<Source<int>> MyCaVllback;

//     void SubscribeFotInfo(MyCallback *cd_)
//     {
//         m_source.Subscribe(cb_);
//     }

// private:
//     Source<int>m_source;
// };

// template <typename dataType>
// void CallbackPtr(dataType)
// {
//     cout << "Callback Pointer() was called" << endl;
// }

// int main()
// {
//     Callback<Thermometer> fridge(CallbackPtr<float>);
//     Source<fridge> thermo;
    

//     thermo.Link(fridge);

//     return (0);
// }
