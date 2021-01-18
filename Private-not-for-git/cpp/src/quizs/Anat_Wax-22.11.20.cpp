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
#include <vector>
#include <list>
#include <cstdlib> // malloc(), free()

// #define FIRST
#define SECOND

#ifdef FIRST
std::string ReverseSentance(std::string str)
{
    // Counter length of word, push it to a list of words:
    std::list<std::string> words;
    size_t i = 0;
    int counter = 0;
    std::string word;

    for (i = 0; i < str.size(); ++i)
    {
        if (' ' != str[i])
        {
            ++counter;
        }
        else // When reached a space:
        {
            // insert(insertion location in destination, src string, index in src, num char to insert):
            word.insert(0, str, i - counter, counter);
            words.push_back(word);
            counter = 0;
            word.clear();
        }
    }

    // Insert the last word in the santence:
    word.insert(0, str, i - counter, counter);
    words.push_back(word);

    std::string result;
    std::list<std::string>::iterator iter = words.end();
    --iter;
    std::string space = " ";

    for (i = 0; i < words.size(); ++i)
    {
        // result.insert(j, iter->c_str(), 0, iter->size());
        result.append(iter->c_str(), 0, iter->size());
        result.append(space);

        --iter;
    }

    return result;
}
#endif //FIRST

std::string ReverseWord(const char *word, size_t len)
{
    size_t i = 0;
    size_t t = len;
    char temp = 0;
    char *result = (char *)malloc(sizeof(char) * len);
    for (; i < len; ++i, --t)
    {
        temp = word[i];
        result[i] = word[t];
        result[t] = temp;
    }
    std::string res(result);

    free(result);


    return res;

    // std::string result = word;

    // size_t j = 0;
    // size_t t = 0;
    // char c = 0;
    // char temp = 0;

    // for (t = 0, j = (word.size() - 1); j > 0; ++t, --j)
    // {
    //     temp = word[j];
    //     c = word.c_str()[t];
    //     // result.at(j) = c;
    //     // result[t] = temp;

    //     word.replace(j, 1, &c);
    //     word.replace(t, 1, &temp);
    // }

    // return result;
}

std::string ReverseWords(std::string str)
{
        // Counter length of word, push it to a list of words:
    std::list<std::string> words;
    size_t i = 0;
    
    int counter = 0;
    std::string word;

    for (i = 0; i < str.size(); ++i)
    {
        if (' ' != str[i])
        {
            ++counter;
        }
        else // When reached a space:
        {
            // insert(insertion location in destination, src string, index in src, num char to insert):
            word.insert(0, str, i - counter, counter);
            words.push_back(word);
            counter = 0;
            word.clear();
        }
    }

    // Insert the last word in the santence:
    word.insert(0, str, i - counter, counter);
    words.push_back(word);

    std::string result;
    std::list<std::string>::iterator iter = words.end();
    --iter;
    std::string space = " ";
    
    for (i = 0; i < words.size(); ++i)
    {
        result = ReverseWord(iter->c_str(), iter->size());
        iter->replace(0, iter->size(), result);
        

        // result.insert(j, iter->c_str(), 0, iter->size());
        result.append(iter->c_str(), 0, iter->size());
        result.append(space);

        --iter;
    }

    return result;
}



#ifdef FIRST
void TestReverseSentance()
{
    std::string string = "hi you, this is me";

    std::string result = ReverseSentance(string);

    std::cout << result << std::endl;
}
#endif // FIRST



int main()
{
    std::string string = "hi you, this is me";

    std::string result = ReverseWords(string);

    std::cout << result << std::endl;

    return 0;
}