/***************************
A hotel manager has to process N bookings of rooms for the next season.
His hotel has K rooms.
Bookings contain an arrival date and a departure date.
He wants to find out whether there are enough rooms in the hotel to satisfy the demand.
Inputs:
- First list for arrival time of booking
- Second list for departure time of booking
- Third is K which denotes the count of rooms
Output:
- A boolean which tells whether its possible to make a booking
false means there are not enough rooms for N booking
true means there are enough rooms for N booking
Example:
Inputs:
- arrivals = [1, 3, 5]
- departures = [2, 6, 10]
- K = 1
Output: false.
At day = 5, there are 2 guests in the hotel. But we have only one room.


Authour: Anat Wax, anatwax@gmail.com
Datecreation: 7.1.21
Version: 1
***************************/
#include <iostream> // cout
#include <vector>
#include <stdlib.h>     /* calloc, free */

bool BookingValid(std::vector<int> arrivals, std::vector<int> departures, int num_rooms)
{
    int *room_occupied = (int *)calloc(departures[departures.size() - 1], sizeof(int));
    int i = 0;
    int j = 0;

    for (i = 0; i < (int)arrivals.size(); ++i)
    {
        for (j = arrivals[i]; j < departures[i]; ++j)
        {
            ++room_occupied[j];
            if (room_occupied[j] > num_rooms)
            {
                return 1;
            }
        }
    }

    free(room_occupied);

    return 0;
}

int main()
{
    std::vector<int> arrivals;
    arrivals.push_back(1);
    arrivals.push_back(3);
    arrivals.push_back(5);
    std::vector<int> departures;
    departures.push_back(2);
    departures.push_back(6);
    departures.push_back(10);
    int num_rooms = 1;

    bool result = BookingValid(arrivals, departures, num_rooms);

    std::cout << "Your request " << (result == false ? "can" : "Cannot") <<
                " be made" << std::endl;

    return 0;
}