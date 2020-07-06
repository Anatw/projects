/*******************************************************************************
Creat the mnt file (all files and folders connected to this mnt are temporary
and will be deleted wwhen a restared is beeing executed - this will demand
re-initializing the folder and files using the steps bellow).

Create RAM disk:
sudo modprobe brd
sudo mkfs.ext2 /dev/ram0

Mount:
mkdir mnt
sudo mount -o sync /dev/ram0 mnt

Copy many files into our “disk”:
sudo cp /usr/include/*.h mnt

Unmount:
sudo umount mnt

!* compile with c99 and onward
gcc fs.c fs_test.c

File system (ext2)
Written by Anat Wax, anatwax@gmail.com
Created: 15.6.20
Reviewer: Yehhuda Levavi
*******************************************************************************/
#include <stdio.h>     /* printf(), size_t */
#include <stdlib.h>    /* malloc(), free(), abs(), size_t */
#include <assert.h>    /* assert() */
#include <stddef.h>    /* offsetof(), size_t */
#include <time.h>      /* time, size_t, srand() */
#include <unistd.h>    /* ssize_t, sleep(), execvp(), fork() */
#include <string.h>    /* size_t, atoi(), memset() */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait() */
#include <fcntl.h>     /* for O parameneters */
#include <sys/stat.h>  /* macroes of i_mode if inodes */
#include <ext2fs/ext2_fs.h>

#include "fs.h"

#define DEFAULT_BLOCK_SIZE (1024)
#define FD_DEVICE "/dev/ram0"

unsigned int block_size = 0;

int main(void)
{
    struct ext2_super_block super;
    struct ext2_group_desc group;
    struct ext2_inode inode;
    struct ext2_inode inode2;
    struct ext2_inode f_inode;
    int fd;
    int found = 0;
    char c = 'n';
    /*char pathname[] = "/amirq/glext.h";*/

    if ((fd = open(FD_DEVICE, O_RDONLY)) == -1)
    {
        perror(FD_DEVICE);
        return (1); /* error while opening the device */
    }

    GetSuperBlock(fd, &super);
    block_size = DEFAULT_BLOCK_SIZE << super.s_log_block_size;
    GetGroupDescriptor(fd, &group);

    ReadInode(fd, &group, 2, &inode); /* read inode 2 (root directory) */
    DirLS(fd, &inode, &group);

    /*FindByPath(fd, &group, pathname);*/

    found = FindFileInDir(fd, &group, &inode, "stdio.h", &f_inode);
    if (found)
    {
        printf("File was found!, print it [Y/n]? ");
        scanf("%c", &c);
        if ((c == 'y') || (c == 'Y'))
            print_file(fd, &f_inode, 1);
    }

    close(fd);

    return (0);
} /* main() */
