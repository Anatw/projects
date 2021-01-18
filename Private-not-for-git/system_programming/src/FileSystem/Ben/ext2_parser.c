/*******************************************************************************
* WS: FS ext2 Parsing Functions                                                *
* Topic: System Programming                                                    *
* Date: 23/06/2020                                                             *
* Author: Ben David Zikri                                                      *
* Reviwer: Yoni Naor                                                           *
*******************************************************************************/
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ext2_parser.h"

void FindSuperBlock(int fd, struct ext2_super_block *super)
{
	lseek(fd, DEFAULT_BLOCK_SIZE, SEEK_SET);
	read(fd, super, sizeof(*super));

	if (super->s_magic != EXT2_SUPER_MAGIC)
	{
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
} /* read super-block */

void FindGroupBlock(int fd, struct ext2_group_desc *group)
{
	lseek(fd, BLOCK_OFFSET(2), SEEK_SET);
	read(fd, group, sizeof(struct ext2_group_desc));
} /* read group descriptor */

void ReadInode(int fd, int inode_no, const struct ext2_group_desc *group,
			   										   struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1) * 
										   sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
} /* read inode from inode_no */

int FindFileInDir(int fd, const struct ext2_group_desc *group_descriptor,
				const struct ext2_inode *inode, const char *file_name_to_search,
				struct ext2_inode *ret_inode)
{

	void *block;
	if (S_ISDIR(inode->i_mode))
	{
		struct ext2_dir_entry_2 *entry;

		unsigned int size = 0;

		if ((block = malloc(block_size)) == NULL)
		{
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		for (int i = 0; i < inode->i_blocks; i++)
		{
			lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
			read(fd, block, block_size);

			entry = (struct ext2_dir_entry_2 *)block;

			while ((size < inode->i_size) && entry->inode)
			{
				char file_name[EXT2_NAME_LEN + 1];
				memcpy(file_name, entry->name, entry->name_len);
				file_name[entry->name_len] = '\0';
				if (strcmp(file_name, file_name_to_search) == 0)
				{
					ReadInode(fd, entry->inode, group_descriptor, ret_inode);
					free(block);
					return (entry->inode);
				}
				entry = (void *)entry + entry->rec_len;
				size += entry->rec_len;
			}
		}
		free(block);
	}

	return (0);
}

void PrintFile(int fd, struct ext2_inode *inode, int level)
{
	char buf[DEFAULT_BLOCK_SIZE] = {'\0'};
    int int_buf[DEFAULT_BLOCK_SIZE / sizeof(int)] = {0};
    int i = 0;

    for (i = 0; inode->i_block[i] != 0; ++i)
    {
        lseek(fd, inode->i_block[i] * DEFAULT_BLOCK_SIZE, SEEK_SET);
        read(fd, buf, DEFAULT_BLOCK_SIZE);
        printf("%s", buf);
    }

    if (inode->i_block[12] != 0) /* fetch 1 level of indirect blocks */
    {
        lseek(fd, inode->i_block[12] * DEFAULT_BLOCK_SIZE, SEEK_SET);
        read(fd, int_buf, DEFAULT_BLOCK_SIZE);

        for (i = 0; int_buf[i] != 0; ++i)
        {
            lseek(fd, int_buf[i] * DEFAULT_BLOCK_SIZE, SEEK_SET);
            read(fd, buf, DEFAULT_BLOCK_SIZE);
            printf("%s", buf);
        }
    }

    if (inode->i_block[13] != 0) /* fetch 2 level of indirect blocks */
    {
        printf("\n\nPrinted already %d indirect blocks, LEAVE ME ALONE!!\n", i);
    }

	if (inode->i_block[14] != 0) /* fetch 3 level of indirect blocks */
    {
        printf("\n\nPrinted already %d indirect blocks, LEAVE ME ALONE!!\n", i);
    }
}

void DirLS(int fd, const struct ext2_inode *inode,
		   const struct ext2_group_desc *group)
{
	void *block;
	char file_name[EXT2_NAME_LEN + 1];

	if (S_ISDIR(inode->i_mode))
	{
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(block_size)) == NULL)
		{ /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		for (size_t i = 0; i < inode->i_blocks; i++)
		{
			lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
			read(fd, block, block_size);

			entry = (struct ext2_dir_entry_2 *)block;
			while ((size < inode->i_size) && entry->inode)
			{
				memcpy(file_name, entry->name, entry->name_len);
				file_name[entry->name_len] = '\0';
				printf("%d, %s\n", entry->inode, file_name);
				entry = (void *)entry + entry->rec_len;
				size += entry->rec_len;
			}
		}

		free(block);
	}
	else
	{
		printf("Isn't a Directory\n");
	}

} /* read_dir() */

void FindByPath(int fd, struct ext2_group_desc *group, char *pathname)
{
	struct ext2_inode inode;
	struct ext2_inode f_inode;
	char c = 'n';
	const char s[2] = "/";
	char *token;
	int found = 0;

	ReadInode(fd, 2, group, &inode);

	token = strtok(pathname, s);

	while (S_ISDIR(inode.i_mode) && token != NULL)
	{
		found = FindFileInDir(fd, group, &inode, token, &f_inode);

		token = strtok(NULL, s);
		inode = f_inode;
	}

	if (found)
	{
		printf("File was found!, print it [Y/n]? ");
		scanf("%c", &c);
		if ((c == 'y') || (c == 'Y'))
			PrintFile(fd, &f_inode, 1);
	}
	else
	{
		printf("File Not Found!\n");
	}
}