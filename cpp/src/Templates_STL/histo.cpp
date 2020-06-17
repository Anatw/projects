/*******************************************************************************
Comment and un-comment the defines to see both phases (one at a time).

Templates + STL (Histo)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: 
*******************************************************************************/
#include <iostream> // cout, cin, cerr
#include <string>   // getline(), compare()
#include <map>      // map
#include <sstream>  // stringstream
#include <vector>   // vector

using namespace std;

int main()
{
    string u_string;
    // Creating a map of string from user (key) and int (num of appearences)
    map<string, int> histo;
    // Creating a vector. It will store the strings thaat are in the map.
    // Vector ewill stor only unique strings, by entring order.
    vector<string> histo_vec;

    do
    {
        getline(cin, u_string);
        // Storing the new string in the map - if it exists - it increses the int:
        histo[u_string]++;

        // If value already exist in map - push it to the end of the vector:
        if (histo[u_string] == 1)
        {
            histo_vec.push_back(u_string);
        }

    } while (u_string.compare(".") != 0);

    // Remove the dot from the vector
    histo_vec.erase(histo_vec.end());

    // Iterating over the map and printing the values:
    map<string, int>::iterator iter;

    for (size_t i = 0; i < histo_vec.size(); ++i)
    {
        iter = histo.find(histo_vec[i]);

        if (1 == iter->second)
        {
            cout << iter->first << endl;
        }
        else
        {
            cout << iter->second << " x " << iter->first << endl;
        }
    }

    return 0;
}
