#include <cstring>  // strlen(), memcpy(), strcmp()
#include <iostream> // cout, cin, cerr
using namespace std;

#include "simple_string.hpp"

inline char* CtorHelper(const char* s)
{
    // In case the user is trying to do a self assignment, the programm will
    // crash,
    // when memcpy is trying to assign an already deleted memory location. So
    // you might want to use an if, but this will cost running time, so this
    // solution with the temp save the if. It better be done with a for loop
    // that copies every element seperatly into temp - to deal with the self
    // assignment.
    char* temp = new char[strlen(s) + 1];
    memcpy(temp, s, (strlen(s) + 1));

    return (temp);
}

String::String(const char* s)
{
    this->m_cstr = CtorHelper(s);
}

String::String(const String& other_) // cctor
{
    this->m_cstr = CtorHelper(other_.m_cstr);
}

String& String::operator=(const String& other_)
{
    char* temp = CtorHelper(other_.m_cstr);

    delete[] this->m_cstr;
    this->m_cstr = temp;

    return (*this);
}

String& String::operator=(const char* other_)
{
    delete[] this->m_cstr;

    this->m_cstr = CtorHelper(other_);

    return (*this);
}

String::~String()
{
    delete[] this->m_cstr;
}

bool operator<(const String& first_, const String& second_)
{
    return (strcmp(first_.Cstr(), second_.Cstr()) < 0);
}

bool operator>(const String& first_, const String& second_)
{
    return (strcmp(first_.Cstr(), second_.Cstr()) > 0);
}

size_t String::Length() const
{
    return (strlen(this->m_cstr));
}

bool operator==(const String& lhs_, const String& rhs_)
{
    return (strcmp(lhs_.Cstr(), rhs_.Cstr()) == 0);
}

ostream& operator<<(ostream& os, const String& p_str)
{
    return (os << p_str.Cstr() << endl);
}
