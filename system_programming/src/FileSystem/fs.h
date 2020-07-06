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
#ifndef ILRD_RD8586_FS_HPP
#define ILRD_RD8586_FS_HPP

#include <ext2fs/ext2_fs.h>

void GetSuperBlock(int fd, struct ext2_super_block *ret_super);

void GetGroupDescriptor(int fd, struct ext2_group_desc *group_des);

void InodeInfo(struct ext2_inode *ret_inode);

void ReadInode(int fd,
               const struct ext2_group_desc *group_descriptor,
               int inode_number,
               struct ext2_inode *ret_inode);

int FindFileInDir(int fd, const struct ext2_group_desc *group_descriptor,
                  const struct ext2_inode *inode, const char *file_name_to_search,
                  struct ext2_inode *ret_inode);

void print_file(int fd,
                struct ext2_inode *inode,
                int level /*= 0 recursive call support*/);

void DirLS(int fd, const struct ext2_inode *inode,
           const struct ext2_group_desc *group);

void FindByPath(int fd, struct ext2_group_desc *group, char *pathname);

void SuperBlockTest();

#endif // ILRD_RD8586_FS_HPP
