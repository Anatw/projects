/*******************************************************************************
                                RCString
                          Written by Anat Wax
						     June 4-7th, 2020
						Reviewer: Kobi Rappaport
*******************************************************************************/
#ifndef RCSTRING_HPP
#define RCSTRING_HPP

#include <cstddef> // size_t

typedef struct RCS
{
    char *m_string;
    int m_rc;
} rcs_t;

class RCString
{
public:
    RCString(const char *str_ = "");
    RCString(const RCString &o_);
    ~RCString();
    RCString &operator=(const RCString &o_); // assignment operator

    size_t Length() const;
    RCString &Concat(const RCString &o_);
    char &operator[](size_t idx_);

    // Returns the string inside the obj.
    inline const char *ToCStr() const
    {
        return (this->s_string->m_string);
    }

    // get_char by value - this is safe.
    inline char operator[](size_t idx_) const
    {
        return (this->s_string->m_string[idx_]);
    }

private:
    rcs_t *s_string;
    enum define
    {
        ONE = 1
    };
};

inline bool operator==(const RCString &s1, const RCString &s2);
inline bool operator!=(const RCString &s1, const RCString &s2);
inline bool operator<(const RCString &s1, const RCString &s2);
inline bool operator>(const RCString &s1, const RCString &s2);

std::ostream &operator<<(std::ostream &os_, const RCString &s_);

#endif //RCSTRING_HPP
