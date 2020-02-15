#include <stdio.h>
#include <assert.h>

#include "funcs.h"

int main()
{
    unsigned int arr[] = {7, 8, 15, 20, 25, 50};
    assert(Pow2(3, 3) == 24);
    assert(Pow2(0, 3) == 0);

    assert(Multiply(3, 3) == 9);
    assert(Multiply(0, 3) == 0);

    assert(IsPowerOfTwo(18) == 0);
    assert(IsPowerOfTwo(32) == 1);

    assert(IsPowerOfTwoLoop(18) == 0);
    assert(IsPowerOfTwoLoop(32) == 1);

    assert(AddOne(56) == 57);
    assert(AddOne(0) == 1);
    assert(AddOne(1) == 2);

    assert(CountOnBits(15) == 4);
    assert(CountOnBits(16) == 1);

    PrintThreeBits(arr, (sizeof(arr) / sizeof(arr[0])));

    assert(ByteMirrorLoop(128) == 1);
    assert(ByteMirrorLoop(50) == 76);
    assert(ByteMirror(128) == 1);
    assert(ByteMirror(50) == 76);

    return 0;
}
