

#include <iostream>
#include <cstdlib>

#include "callback2.hpp"
#include "dir_monitor.hpp"

void PrintA()
{
    std::cout << "I am just printing A's, nothing more...\n" << std::endl;
}

int main()
{
    system("clear");

    std::cout << "\n\nMain dir_monitor test\n\n" << std::endl;
    std::cout << "---------------------" << std::endl;

    Callback first_call(PrintA);

    DirMonitor main_monitor("/home/liorcoeh/git/lior-cohen/cpp/sourceCR/check");


    // explicit DirMonitor(std::string dir_path);
    // void Subscribe(Callback<Dispatcher<std::string> > *callback);
    // void UnSubscribe(Callback<Dispatcher<std::string> > *callback);
    // void StartMonitoring();

    return (0);
}

