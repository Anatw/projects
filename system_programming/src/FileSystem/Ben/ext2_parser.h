/*******************************************************************************
* WS: FS ext2 Parsing Header                                                   *
* Topic: System Programming                                                    *
* Date: 23/06/2020                                                             *
* Author: Ben David Zikri                                                      *
* Reviwer: Yoni Naor                                                           *
*******************************************************************************/
#include <ext2fs/ext2_fs.h>

#define DEFAULT_BLOCK_SIZE (1024)                 
#define FD_DEVICE "/dev/ram0"
#define BLOCK_OFFSET(block) (DEFAULT_BLOCK_SIZE + (block - 1) * block_size)

unsigned int block_size;

void FindSuperBlock(int fd, struct ext2_super_block *super);

void FindGroupBlock(int fd, struct ext2_group_desc *group);

void ReadInode(int fd, int inode_no, 
				const struct ext2_group_desc *group, struct ext2_inode *inode);

void DirLS(int fd, const struct ext2_inode *inode, 
										   const struct ext2_group_desc *group);

int FindFileInDir(int fd, const struct ext2_group_desc *group_descriptor, 
				 const struct ext2_inode *inode,const char *file_name_to_search, 
												  struct ext2_inode *ret_inode);

void PrintFile(int fd, struct ext2_inode* inode, int level);

void FindByPath(int fd, struct ext2_group_desc *group, char *pathname);