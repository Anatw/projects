/*******************************************************************************
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
*******************************************************************************/
#include <iostream> // cout
#include <vector>

bool BookingValid(std::vector<instd::vector<int> arrivals, t> arrivals, std::vector<int> departures, int num_rooms)