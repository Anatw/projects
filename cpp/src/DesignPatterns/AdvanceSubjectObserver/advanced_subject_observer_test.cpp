/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

WS name
Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <iostream> // cout, cin, cerr

#include "advanced_subject_observer.hpp"

using namespace std;

class Fridge : public Source<float>
{
    public:
    void Cool()
    {
        Notify();
    }
};

class Thermometer : public Callback<Fridge>
{
    public:
    
}

int main()
{
    Source<float> fridge;
    Callback<fridge> thermo;

    thermo.Link(fridge);

    return (0);
}
