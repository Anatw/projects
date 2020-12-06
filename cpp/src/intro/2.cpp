enum E {AA, BB, CC, DD};
enum E2 {TT, KK};
enum E e = 2;
enum E2 e2 = AA;
// E2 e22 = KK;
++e;
int i = e;

/*
anat@ubuntu:~/anat-wax/cpp/src/intro$ pdfree 2.cpp 
2.cpp:3:12: error: invalid conversion from ‘int’ to ‘E’ [-fpermissive]
    3 | enum E e = 2;
      |            ^
      |            |
      |            int
2.cpp:4:14: error: cannot convert ‘E’ to ‘E2’ in initialization
    4 | enum E2 e2 = AA;
      |              ^~
      |              |
      |              E
2.cpp:6:1: error: expected unqualified-id before ‘++’ token
    6 | ++e;
      | ^~
 */