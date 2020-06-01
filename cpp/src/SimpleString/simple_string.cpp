#include <iostream> /* cout, cin, cerr */
#include <string>
#include <bits/stdc++.h>
#include <cstring> 
using namespace std;

/*#define C_STRING*/
#define CPP_STRING

#ifndef C_STRING
class String
{
public :
    String(string s)
    {
        this->str = s;
        this->m_cstr = new char[this->str.length() + 1];
        strcpy(this->m_cstr, this->str.c_str());
        //this->m_cstr = const_cast<char*>(this->str.c_str());
        
        /* With strcpy - must activate the Dtor:
        this->m_cstr = new char[this->str.length() + 1];
        strcpy(this->m_cstr, this->str.c_str());*/
        
        /* 1. Attempt to use strdup (failure...):
        this->m_cstr = strdup(const_cast<char*>(this->str));*/
    }

    /*~String()
    {
        delete[] this->m_cstr;
    }*/
 
    int operator<(String other)
    {
        if (this->str.length() < other.str.length() &&
            strlen(this->m_cstr) < strlen(other.m_cstr))
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }

    int operator>(String other)
    {
        if (this->str.length() > other.str.length() &&
            strlen(this->m_cstr) > strlen(other.m_cstr))
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    
    String& operator=(String other)
    {
        this->str = other.str;
        this->m_cstr = other.m_cstr;

        return (*this);
    }
    
    inline int Length() const
    {
        return (str.length());
    }
    
    inline char *Cstr() const
    {
        return (this->m_cstr);
    }

private :
    friend std::ostream& operator<<(std::ostream& os, const String& p_str);
    friend String& operator<<(String& os, ostream& (*pf)(ostream&));
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator==(const char* o_, const String& rhs);
    char *m_cstr;
    string str;
};
#endif /* C_STRING */


int main()
{
    String s1("hello"); //  s1 now equals to "hello".
    // Create new String object called 's2', which is actually a copy of s1 (contains "hello"):
    String s2(s1);
    s1 = s2; // s2 is a copy of s1 (contains "hello").
    size_t string_length = s2.Length();
    cout << string_length << endl;
    s1.Cstr(); // return m_cstr
    cout << s1.Cstr() << endl;

    cout << s1 << endl;
    s1 == s2;
    "123" == s1;
    cout << "s1 > s2: " << (s1 > s2) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;

    const char *s3 = "hello";
    const char *s4 = "hi";

    cout << "s3 < s4: " << (s3 < s4) << endl;

    s3 == s4;

    return (0);
}

ostream& operator<<(ostream& os, const String& p_str)
{
    return os << p_str.str;
}

String& operator<<(String& os, ostream& (*pf)(ostream&))
{
    return operator<< (os, pf);
}

bool operator==(const String& lhs, const String& rhs)
{
    if (lhs.str == rhs.str && lhs.m_cstr == rhs.m_cstr)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool operator==(const char* o_, const String& rhs)
{
    if (strcmp(o_, rhs.str.c_str()) || strcmp(o_, rhs.m_cstr))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#ifndef CPP_STRING
class String
{
    s_;

    A (stf::string const &S) : s_ (s)
    {
        str = s;
    }

public :
    String(string s)
    {
        std::string str = s;
    }
    int Length()
    {
        return (str.length());
    }
    /*Cstr()
    {
        return (cstr, str.c_str)   
    }*/
private :
    char * m_cstr;
    string str;
};
#endif /* CPP_STRING */
