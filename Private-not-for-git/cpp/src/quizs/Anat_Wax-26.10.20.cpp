/*******************************************************************************
1.
pseudo+code
write a function that says whether the given strings are isomorphic or not. Two strings are said to be isomorphic if there is a one to one mapping between all characters in both strings
Example
INPUT
s1  = “aadc”
s2 =  “mmkl”

Input:  str1 = "aab", str2 = "xxy"
Output: True
'a' is mapped to 'x' and 'b' is mapped to 'y'.


2.
pseudo : Check for balanced parentheses in an expression


Authour: Anat Wax anatwax@gmail.com
Datecreation: 26.10.2020
*******************************************************************************/
#include <iostream> // cout
#include <limits> // interger min + max values
#include <cstdlib> // calloc()


bool IsIsomorphic(std::string first, std::string second)
{
    unsigned char *table_f = (unsigned char *)calloc(255, sizeof(char));
    unsigned char *table_s = (unsigned char *)calloc(255, sizeof(char));

    size_t i = 0; // index for first
    size_t j = 0; // index for second
    unsigned const char *str1 = (unsigned char*)first.c_str();
    unsigned const char *str2 = (unsigned char*)second.c_str();

    for (; i < first.size() && j < second.size(); ++i, ++j)
    {
        if (table_f[str1[i]] == 0)
        {
            table_f[str1[i]] = str2[j];
        }
        else
        {
            if (table_f[str1[i]] != str2[j])
            {
                return false;
            }
        }

        if (table_s[str2[j]] == 0)
        {
            table_s[str2[j]] = str1[i];
        }
        else
        {
            if (table_s[str2[j]] != str1[j])
            {
                return false;
            }
        }
    }

    return true;
}

void TestCase1()
{
    std::string str1 = "aab";
    std::string str2 = "xxy";

    std::cout << IsIsomorphic(str1, str2) << " == true" << std::endl;
}



void TestCase2()
{
    std::string s = "egg";
    std::string t = "add";

    std::cout << IsIsomorphic(s, t) << " == true" << std::endl;
}


void TestCase3()
{
    std::string s = "foo";
    std::string t = "bar";

    std::cout << IsIsomorphic(s, t) << " == false" << std::endl;
}


void TestCase4()
{
    std::string s = "paper";
    std::string t = "title";
    
    std::cout << IsIsomorphic(s, t) << " == true" << std::endl;
}

int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();

    return 0;
}