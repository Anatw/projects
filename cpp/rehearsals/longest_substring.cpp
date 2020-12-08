/*******************************************************************************
Title & Description: Master Storage Manager - part of the Master in the 
final project.
This part is in charge of all the documentation and maintenance of the 
mapping between the offsets of the memory and the Minion responsible to 
operate

Authour: Anat Wax, anatwax@gmail.com
Reviewer: 
Datecreation: 20.09.2020
Version: 1
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <string>
#include <map>
#include <cstring>
#include <cstdlib>

void LongestSubstring(const std::string &str, const size_t num_char, char *result)
{
    size_t i = 0;
    size_t j = 0;
    size_t counter = 0;
    size_t temp_counter = 0;
    int begin = 0;
    int temp_begin = 0;
    size_t char_counter = 0;
    std::map<char, int> map; // char = character, int = character counter.

    // For each character in the string - iteratre the rest of the string and count inner string length:
    for (; i < str.size(); ++i)
    {
        temp_begin = i;
        map.insert(std::make_pair(str[i], 1));
        ++char_counter;
        ++temp_counter;

        for (j = i + 1; j < str.size(); ++j)
        {
            if (map.find(str[j])->second == 0) // str[j] is a new char.
            {
                // Check if it is possible to add more characters to the map
                if (char_counter < num_char)
                {
                    map.insert(std::make_pair(str[j], 1));
                    ++char_counter;
                }
                else
                {
                    break;
                }
            }

            ++temp_counter;
        }

        if (temp_counter > counter)
        {
            counter = temp_counter;
            begin = temp_begin;
        }

        char_counter = 0;
        temp_counter = 0;
        map.clear();
    }

    // Copy the relevant sub-string into the result string:
    for (i = 0; i < counter; ++i, ++begin)
    {
        result[i] = str[begin];
    }

    result[i] = '\n';
}

int main()
{
    std::string string = "abcbdbdbbdcdabd";
    char *result = (char *)malloc(sizeof(char) * string.size());
    LongestSubstring(string, 6, result);

    std::cout << "substring of the string \n\"" << string << "\" is " << "\n\"" << result << "\"\n";

    return 0;
}

/*
std::string LongestSubstring(const std::string &str, const int num_char)
{
    if (str.size() <= num_char)
    {
        return str;
    }

    int counter = 0;
    int temp_counter = 0;
    int char_counter = 0;
    int begin = 0;
    std::map<char, int> map; // char = character, int = character counter.
    int i = 0;
    int j = 0;
    int next_char = 0;

    for (i = 0; i < str.size(); ++i)
    {
        // If char is already in map - continue counting
        if (map.find(str[i])->second > 0)
        {
            ++counter;
        }
        // Else - check if you can add it to the map. If not - save the counter.
        else
        {
            if (num_char < char_counter)
            {
                map.insert(std::make_pair(str[i], 1));
                next_char = i;
            }
            else
            {
                // Saving the max counter that begin with the specific character inside the character value in the map.
                map.find(str[begin])->second = counter;
                counter = 0;
                begin = i - 1;
                i = next_char;
            }
        }
    }

    // Find the biggest value inside tht map. Find the firt character in the string for this value. Create a new string stating with this caaracter, until character + counter location. Return this string to the user.

    std::map<char, int>::iterator iterator = map.begin();
    std::map<char, int>::iterator end = map.end();
    std::map<char, int>::iterator chosen = iterator;

    // Find longest counter;
    for (++iterator; iterator != end; ++iterator)
    {
        if (iterator->second > chosen->second)
        {
            chosen = iterator;
        }
    }

    for (i = 0; i < str.size(); ++i)
    {
        if (chosen->first == str[i])
        {
            break;
        }
    }

    std::string result;

    memcpy(&result, &str[i], chosen->second);

    return result;
}
*/