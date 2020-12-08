#include <iostream> /* cout, cin, cerr */

#include "Q14.h"

using namespace std;

void test()
{
    foo();
}

int main()
{
    foo();

    return (0);
}

inline void foo()
{
    std::cout << "kkk";
}


/*
anat@ubuntu:~/git/anat-wax/cpp/src/intro$ nm ./a.out - -n

./a.out:
                 U __cxa_atexit@@GLIBC_2.2.5
                 w __cxa_finalize@@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@@GLIBC_2.2.5
                 U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4
0000000000000688 T _init
00000000000006f0 T _start
0000000000000720 t deregister_tm_clones
0000000000000760 t register_tm_clones
00000000000007b0 t __do_global_dtors_aux
00000000000007f0 t frame_dummy
00000000000007fa T main
000000000000080a t _Z41__static_initialization_and_destruction_0ii
0000000000000853 t _GLOBAL__sub_I_main
0000000000000868 W _Z3foov
0000000000000890 T __libc_csu_init
0000000000000900 T __libc_csu_fini
0000000000000904 T _fini
0000000000000910 R _IO_stdin_used
0000000000000914 r _ZStL19piecewise_construct
000000000000091c r __GNU_EH_FRAME_HDR
0000000000000ad4 r __FRAME_END__
0000000000200d88 t __frame_dummy_init_array_entry
0000000000200d88 t __init_array_start
0000000000200d98 t __do_global_dtors_aux_fini_array_entry
0000000000200d98 t __init_array_end
0000000000200da0 d _DYNAMIC
0000000000200fa0 d _GLOBAL_OFFSET_TABLE_
0000000000201000 D __data_start
0000000000201000 W data_start
0000000000201008 D __dso_handle
0000000000201010 B __bss_start
0000000000201010 D _edata
0000000000201010 D __TMC_END__
0000000000201020 B _ZSt4cout@@GLIBCXX_3.4
0000000000201130 b completed.7698
0000000000201131 b _ZStL8__ioinit
0000000000201138 B _end
*/