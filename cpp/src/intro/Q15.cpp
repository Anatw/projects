#include <iostream> /* cout, cin, cerr */
#include <string>

#include "Q15.h"


int main()
{
    int arr[12];

    std::cout << Max<int>(3,5) << " " << Max<double>(3.7, 12.9) << " ";
    std::cout << Max<float>(3.8, 4.5) << " " << Max<char>('g', 'h') << " ";
    //std::cout << Max<char[5]>("hello", "there") << std::endl;
    std::cout << Max<int*>(arr, arr + 8) << std::endl;
    std::cout << Max('a', 'b') << std::endl;

    return (0);
}

template <typename T>
T Max(T t1, T t2)
{
    return (t1 > t2) ? t1 : t2;
}
/*
                 U __cxa_atexit@@GLIBC_2.2.5
                 w __cxa_finalize@@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@@GLIBC_2.2.5
                 U __stack_chk_fail@@GLIBC_2.4
                 U _ZNSolsEd@@GLIBCXX_3.4
                 U _ZNSolsEi@@GLIBCXX_3.4
                 U _ZNSolsEPFRSoS_E@@GLIBCXX_3.4
                 U _ZNSolsEPKv@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@@GLIBCXX_3.4
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4
00000000000008b0 T _init
0000000000000980 T _start
00000000000009b0 t deregister_tm_clones
00000000000009f0 t register_tm_clones
0000000000000a40 t __do_global_dtors_aux
0000000000000a80 t frame_dummy
0000000000000a8a T main
0000000000000b99 t _Z41__static_initialization_and_destruction_0ii
0000000000000be2 t _GLOBAL__sub_I_main
0000000000000bf7 W _Z3MaxIiET_S0_S0_
0000000000000c13 W _Z3MaxIdET_S0_S0_
0000000000000c3b W _Z3MaxIPiET_S1_S1_
0000000000000c5d W _Z3MaxIcET_S0_S0_
0000000000000c80 T __libc_csu_init
0000000000000cf0 T __libc_csu_fini
0000000000000cf4 T _fini
0000000000000d00 R _IO_stdin_used
0000000000000d08 r _ZStL19piecewise_construct
0000000000000d20 r __GNU_EH_FRAME_HDR
0000000000000f5c r __FRAME_END__
0000000000201d50 t __frame_dummy_init_array_entry
0000000000201d50 t __init_array_start
0000000000201d60 t __do_global_dtors_aux_fini_array_entry
0000000000201d60 t __init_array_end
0000000000201d68 d _DYNAMIC
0000000000201f68 d _GLOBAL_OFFSET_TABLE_
0000000000202000 D __data_start
0000000000202000 W data_start
0000000000202008 D __dso_handle
0000000000202010 B __bss_start
0000000000202010 D _edata
0000000000202010 D __TMC_END__
0000000000202020 B _ZSt4cout@@GLIBCXX_3.4
0000000000202130 b completed.7698
0000000000202131 b _ZStL8__ioinit
0000000000202138 B _end
*/