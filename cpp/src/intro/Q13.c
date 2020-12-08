#include <stdio.h>

int i = 3;

int main()
{
    int *ip = (int *)&i;
    *ip = 5;
    gdint arr[i];

    printf("%d %d\n", i, *ip);

    return (0);
}
/*
anat@ubuntu:~/git/anat-wax/cpp/src/intro$ nm q13c -n
                 w __cxa_finalize@@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __libc_start_main@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
00000000000004f0 T _init
0000000000000540 T _start
0000000000000570 t deregister_tm_clones
00000000000005b0 t register_tm_clones
0000000000000600 t __do_global_dtors_aux
0000000000000640 t frame_dummy
000000000000064a T main
0000000000000690 T __libc_csu_init
0000000000000700 T __libc_csu_fini
0000000000000704 T _fini
0000000000000710 R _IO_stdin_used
0000000000000714 r _ZL1i
0000000000000720 r __GNU_EH_FRAME_HDR
0000000000000864 r __FRAME_END__
0000000000200db8 t __frame_dummy_init_array_entry
0000000000200db8 t __init_array_start
0000000000200dc0 t __do_global_dtors_aux_fini_array_entry
0000000000200dc0 t __init_array_end
0000000000200dc8 d _DYNAMIC
0000000000200fb8 d _GLOBAL_OFFSET_TABLE_
0000000000201000 D __data_start
0000000000201000 W data_start
0000000000201008 D __dso_handle
0000000000201010 B __bss_start
0000000000201010 b completed.7698
0000000000201010 D _edata
0000000000201010 D __TMC_END__
0000000000201018 B _end
*/