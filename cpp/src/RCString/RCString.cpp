/*******************************************************************************
                                RCString
                          Written by Anat Wax
						     June 4-7th, 2020
						Reviewer: Kobi Rappaport
*******************************************************************************/
#include <iostream>  /* cout, cin, cerr */
#include <string.h>  // strcmp()
#include <exception> // bad_alloc
#include <new>       // operator new

#include "RCString.hpp"

using namespace std;

void DecreaseOrDelete(rcs_t *string_member_);

/*******************************************************************************
                          Constructos + Distructor:
*******************************************************************************/
//Code inside 'try' will throw a bad_alloc if allocation fail.
RCString::RCString(const char *str_)
{
    size_t length = strlen(str_) + ONE;
    this->s_string = new rcs_t;
    try
    {
        this->s_string->m_string = (char *)operator new(length);
    }
    catch (bad_alloc &e)
    {
        cerr << e.what() << '\n';
        delete this->s_string;
        throw(bad_alloc());
    }

    memcpy(this->s_string->m_string, str_, length);
    this->s_string->m_rc = ONE;
}

RCString::RCString(const RCString &o_) //cctor
{
    this->s_string = o_.s_string;
    ++this->s_string->m_rc;
}

RCString::~RCString()
{
    DecreaseOrDelete(this->s_string);
}

RCString &RCString::operator=(const RCString &o_) // assignment operator
{
    // Check for the case the user send the same string as value
    if (this == &o_)
    {
        return (*this);
    }

    DecreaseOrDelete(this->s_string);

    // Pointing to the new string:
    this->s_string = o_.s_string;
    ++this->s_string->m_rc;

    return (*this);
}

/*******************************************************************************
                              Class functions:
*******************************************************************************/
size_t RCString::Length() const
{
    return (strlen(this->s_string->m_string));
}

RCString &RCString::Concat(const RCString &o_)
{
    size_t this_length = strlen(this->s_string->m_string);
    size_t o_length = strlen(o_.s_string->m_string);

    char *buffer = (char *)operator new(this_length + o_length + ONE);
    // char *buffer = new char[this_length + o_length + ONE];

    // Copy the first string into the new buffer.
    static size_t i = 0;
    while ('\0' != this->s_string->m_string[i])
    {
        for (i = 0; i < this_length; ++i)
        {
            buffer[i] = this->s_string->m_string[i];
        }
    }

    // Regarding the expression: 'this->s_string->m_string = buffer;', in this
    // state is still don't matter if the string is changed because I'm changing
    // is into the exctly same string (changing him to himeself).
    if (1 < this->s_string->m_rc)
    {
        --this->s_string->m_rc;

        try
        {
            this->s_string = new rcs_t;
        }
        catch (const bad_alloc &e)
        {
            cerr << e.what() << '\n';
            delete[] buffer;
            throw bad_alloc();
        }

        this->s_string->m_string = buffer;
        this->s_string->m_rc = ONE;
    }
    else
    {
        delete[] this->s_string->m_string;
    }

    // Copy the second string as appended to
    // the first one (inside the new buffer).
    size_t j = 0;
    while ('\0' != o_.s_string->m_string[j])
    {

        for (j = 0; j < o_length; ++j, ++i)
        {
            buffer[i] = o_.s_string->m_string[j];
        }
    }

    buffer[i] = '\0';

    //this->s_string->m_string = buffer;

    return (*this);
}

// get_char by reference - this is dangerous!! the user will be able to change
// the value inside the string. This is why a copy of the original string will
// be made, the string will be seperated from the struct it is located in and
// will be attrached to a new rcs_t struct.
char &RCString::operator[](size_t idx_)
{
    // If m_rc contain more than one string - the user might change the
    // character (when this function returns), and this character will be
    // changed in all instances of this string, so - a new rcs_t struct is
    // created and inside it - the string that will be returned to the user.m_rc
    // should be deduced for the old string struct.
    if (1 < this->s_string->m_rc)
    {
        char *buffer = this->s_string->m_string;
        --this->s_string->m_rc;

        this->s_string = new rcs_t;

        try
        {
            this->s_string->m_string = (char *)operator new(strlen(buffer) + ONE);
        }
        catch (const bad_alloc &e)
        {
            cerr << e.what() << '\n';
            delete[] this->s_string;
            throw bad_alloc();
        }

        memcpy(this->s_string->m_string, buffer, (strlen(buffer) + ONE));
        this->s_string->m_rc = ONE;
    }

    return (this->s_string->m_string[idx_]);
}

/*******************************************************************************
                                Operators:
*******************************************************************************/
inline bool operator==(const RCString &s1, const RCString &s2)
{
    return (strcmp(s1.ToCStr(), s2.ToCStr()) == 0);
}

inline bool operator!=(const RCString &s1, const RCString &s2)
{
    return (strcmp(s1.ToCStr(), s2.ToCStr()) != 0);
}

inline bool operator<(const RCString &s1, const RCString &s2)
{
    return (strcmp(s1.ToCStr(), s2.ToCStr()) < 0);
}

inline bool operator>(const RCString &s1, const RCString &s2)
{
    return (strcmp(s1.ToCStr(), s2.ToCStr()) > 0);
}

ostream &operator<<(ostream &os_, const RCString &s_)
{
    return (os_ << s_.ToCStr() << endl);
}

/*******************************************************************************
                             Utility functions:
*******************************************************************************/
void DecreaseOrDelete(rcs_t *string_member_)
{
    // Check the counter - if counter = 1 need to delete
    // if counter is more than one, simply --
    if (1 == string_member_->m_rc)
    {
        delete string_member_->m_string; // delete a struct
        delete string_member_;           // delete an object
    }
    else
    {
        --string_member_->m_rc;
    }
}
