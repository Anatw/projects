#include <iostream> /* cout, cin, cerr */

using namespace std;

#include "simple_string.hpp"

int main()
{
    String s1("hello"); //  s1 now equals to "hello".
    // Create new String object called 's2', which is actually a copy of s1 (contains "hello"):
    String s2(s1);
    // s1 = s2; // s2 is a copy of s1 (contains "hello").
    cout << "s1 address: " << s1 << endl;
    cout << "s2 address: " << s2 << endl;
    size_t string_length = s2.Length();
    cout << string_length << endl;
    s1.Cstr(); // return m_cstr
    cout << s1.Cstr() << endl;

    cout << s1 << endl;
    s1 == s2;
    cout << "\"123\" == s1?: " << ("123" == s1) << endl;
    cout << "s1 > s2: " << (s1 > s2) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;

    String s6;
    cout << "s6: " << s6 << endl;

    const char *s3 = "hello";
    const char *s4 = "hi";
    s2 = "Shiny!";
    cout << "s2: " << s2 << endl;

    cout << "s3 < s4: " << (s3 < s4) << endl;

    cout << "Are s3 and s4 are equal?: " << (s3 == s4) << endl;

    return (0);
}

/* bool - return:
0 = false
1 = true 
*/
