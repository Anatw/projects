/*******************************************************************************
Implement the following class:

class Array
{
public:
    Array(int size)
    void setval (int indx, int val); // O(1)
    int getval (int indx) const; // O(1)
    void setall (int val); // O(1)
};

Note: performance is of the highest importance!

Written by Anat Wax, anatwax@gmail.com
Created: 6.8.20
*******************************************************************************/
#include <assert.h>
#include <iostream> // cout, cin, cerr
#include <string.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//               Array class definition and declaration:                      //
////////////////////////////////////////////////////////////////////////////////

class Array
{
public:
    Array(int size);
    ~Array();
    void SetVal(int index, int val);
    int GetVal(int val) const;
    void SetAll(int val);

private:
    struct element
    {
        int value;
        size_t version;
    };

    element* m_array;
    element m_set_all;

    int m_size;
};

Array::Array(int size) : m_size(size)
{
    m_array = new struct element[size];
    memset(m_array, 0, size);

    m_set_all.value = 0;
    m_set_all.version = 0;
}

Array::~Array()
{
    delete[] m_array;
}

void Array::SetVal(int index, int val)
{
    assert(m_array);

    if (index > m_size)
    {
        throw runtime_error("index requested is out of range");
    }

    m_array[index].value = val;
    ++m_array[index].version;
}

int Array::GetVal(int index) const
{
    assert(m_array);

    if (index > m_size)
    {
        throw runtime_error("index requested is out of range");
    }

    if (m_array[index].version > m_set_all.version)
    {
        return (m_array[index].value);
    }
    else
    {
        return (m_set_all.value);
    }
}

void Array::SetAll(int val)
{
    assert(m_array);

    m_set_all.value = val;
    ++m_set_all.version;
}
////////////////////////////////////////////////////////////////////////////////
//                             Main function: //
////////////////////////////////////////////////////////////////////////////////

int main()
{
    int size = 10;
    Array array(size);
    array.SetVal(1, 1);
    array.SetVal(2, 2);
    array.SetVal(3, 3);
    array.SetVal(4, 4);
    array.SetVal(5, 5);
    array.SetVal(6, 6);
    array.SetVal(7, 7);
    array.SetVal(8, 8);
    array.SetVal(9, 9);

    // for (int i = 0; i < size; ++i)
    // {
    //     array.SetVal(i, i);
    // }

    for (int i = 0; i < size; ++i)
    {
        cout << array.GetVal(i) << endl;
    }

    array.SetAll(12);

    cout << "after setting all to 12\n\n" << endl;

    for (int i = 0; i < size; ++i)
    {
        cout << array.GetVal(i) << endl;
    }

    array.SetVal(4, 99);
    array.SetVal(6, 80);
    array.SetVal(2, 20587);

    cout << "\nSetting the value of index 4(99), 6(80) and 2(20587)\n\n after "
            "the change:\n"
         << endl;

    for (int i = 0; i < size; ++i)
    {
        cout << array.GetVal(i) << endl;
    }

    return (0);
}

/*
Needed to chenge for correctnes:
1. wrong syntax for creating a new struct of elements.
2. forgot to add testing for out-of-range.
*/
