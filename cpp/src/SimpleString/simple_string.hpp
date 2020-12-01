#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

class String
{
public:
    /* The program is not supporting a case in which an object of type 'String' is  beeing assigned to 'NULL' */
    String(const char *s = "");
    String(const String &o_);
    ~String();
    String &operator=(const String &other);
    String &operator=(const char *other_);
    //
    size_t Length() const;
    inline char *Cstr() const
    {
        return (this->m_cstr);
    }

private:
    char *m_cstr;
};

bool operator<(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator==(const String &lhs, const String &rhs);

std::ostream &operator<<(std::ostream &os, const String &p_str);

#endif //SIMPLE_STRING_H
