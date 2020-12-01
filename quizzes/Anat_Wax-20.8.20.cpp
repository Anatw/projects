/*******************************************************************************
implement a string class suporting these functionalities:

String s1("aaa");
String s2 = "bbb";
String s3(s2);
String s4;

s4 = s2;
s3[2] = 'k';

Written by Anat Wax, anatwax@gmail.com
Created: 20.8.20
*******************************************************************************/

#include <cstddef>  // size_t
#include <iostream> // ostream
#include <new>
#include <string.h>

class String
{
public:
    String(const char* str_ = "");
    String(const String& o_);
    virtual ~String();
    String& operator=(const String& other_);
    String& operator=(const char* other_);

    inline const char* ToCStr() const
    {
        return (m_string);
    }

    inline char& operator[](size_t index)
    {
        return (m_string[index]);
    }

private:
    char* m_string;
};

////////////////////////////////////////////////////////////////////////////////

String::String(const char* str_)
{
    size_t length = strlen(str_) + 1;

    try
    {
        m_string = (char*)operator new(length);
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        delete m_string;
        throw(std::bad_alloc());
    }

    memcpy(m_string, str_, length);
}

////////////////////////////////

String::String(const String& o_)
{
    size_t length = strlen(o_.m_string) + 1;
    m_string = (char*)operator new(length);
    memcpy(m_string, o_.m_string, length);
}

////////////////////////////////

String::~String()
{
    delete m_string;
}

////////////////////////////////

String& String::operator=(const String& o_)
{
    // If user send the same string as value
    if (this == &o_)
    {
        return (*this);
    }

    size_t length = strlen(o_.m_string) + 1;
    char* buffer = (char*)operator new(length);
    memcpy(buffer, o_.m_string, length);

    delete m_string;
    m_string = buffer;

    return (*this);
}

////////////////////////////////

String& String::operator=(const char* other_)
{
    size_t length = strlen(other_) + 1;
    char* buffer = (char*)operator new(length);
    memcpy(buffer, other_, length);

    delete m_string;
    m_string = buffer;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    String s1("aaa");
    String s2 = "bbb";
    String s3(s2);
    String s4;

    std::cout << s1.ToCStr() << std::endl;
    std::cout << s2.ToCStr() << std::endl;
    std::cout << s3.ToCStr() << std::endl;

    s4 = s2;
    s3[2] = 'k';

    std::cout << s4.ToCStr() << std::endl;
    std::cout << s3.ToCStr() << std::endl;

    return (0);
}
