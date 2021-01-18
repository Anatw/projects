/*******************************************************************************
* WS: FS ext2 Parsing Tests                                                    *
* Topic: System Programming                                                    *
* Date: 23/06/2020                                                             *
* Author: Ben David Zikri                                                      *
* Reviwer: Yoni Naor                                                           *
*******************************************************************************/
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "ext2_parser.h"

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
	char pathname[] = "/amirq/glext.h";

	if ((fd = open(FD_DEVICE, O_RDONLY)) == -1) 
	{
		perror(FD_DEVICE);
		return (1);  /* error while opening the device */
	}
	
	FindSuperBlock(fd, &super);
	block_size = DEFAULT_BLOCK_SIZE << super.s_log_block_size;
	FindGroupBlock(fd, &group);

	ReadInode(fd, 2, &group, &inode); /* read inode 2 (root directory) */
	DirLS(fd, &inode, &group);

	FindByPath(fd, &group, pathname);

	found = FindFileInDir(fd, &group, &inode, "stdio.h", &f_inode);
	if(found)
	{
		printf("File was found!, print it [Y/n]? ");
		scanf("%c", &c);
		if ((c == 'y') || (c == 'Y'))
			PrintFile(fd, &f_inode, 1);
	}
	
	close(fd);

	return (0);
} /* main() */


