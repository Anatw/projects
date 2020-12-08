#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool is_pangram(const char* str_in)
{
    int i = 0;
    int length = 26;
    char lut[26] = {0};

    for (i = 0; *str_in; ++i, ++str_in)
    {
        if (0 <= ((tolower(*str_in)) - 'a') || (26 > (tolower(*str_in)) - 'a'))
        {
            ++lut[(tolower(*str_in)) - 'a'];
        }
    }

    for (i = 0; i < length; ++i)
    {
        if (0 == lut[i])
        {
            return (false);
        }
    }
    return (true);
}

bool is_pangram(const char* str_in);
void tester(const char* str_in, bool answer);

int main()
{

    printf("%d\n", is_pangram("The quick, brown fox jumps over the lazy dog!"));
    assert(1 == is_pangram("The quick, brown fox jumps over the lazy dog!"));
    assert(0 == is_pangram("The quick, brown fox jumped over the lazy dog!"));

    return (0);
}
