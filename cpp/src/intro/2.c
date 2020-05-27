enum E {AA, BB, CC, DD};
enum E2 {TT, KK};
enum E e = 2;
enum E2 e2 = AA;
// E2 e22 = KK;
++e;
int i = e;

/*
anat@ubuntu:~/git/anat-wax/cpp/src/intro$ pd 2.cpp
2.cpp:3:12: error: invalid conversion from ‘int’ to ‘E’ [-fpermissive]
 enum E e = 2;
            ^
2.cpp:4:14: error: cannot convert ‘E’ to ‘E2’ in initialization
 enum E2 e2 = AA;
              ^~
2.cpp:6:1: error: expected unqualified-id before ‘++’ token
 ++e;
 ^~
anat@ubuntu:~/git/anat-wax/cpp/src/intro$ gd 2.c
2.c:5:1: error: C++ style comments are not allowed in ISO C90
 // E2 e22 = KK;
 ^
2.c:5:1: error: (this will be reported only once per input file)
2.c:6:1: error: expected identifier or ‘(’ before ‘++’ token
 ++e;
 ^~
2.c:7:9: error: initializer element is not constant
 int i = e;
 */