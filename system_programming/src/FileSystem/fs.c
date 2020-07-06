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

#define BLOCK_SIZE (1024)
#define BLOCK_OFFSET(block) (BLOCK_SIZE + (block - 1) * BLOCK_SIZE)
/*

*/

/* Super block is the main header of the memory pool: */
void GetSuperBlock(int fd, struct ext2_super_block *ret_super)
{
    /* Move the fd to a position after the "boot block": */
    lseek(fd, BLOCK_SIZE, SEEK_SET);
    read(fd, ret_super, sizeof(*ret_super)); /* read super-block */

    if (ret_super->s_magic != EXT2_SUPER_MAGIC)
    {
        perror("not an ext2 data\n");
        exit(1);
    }
}

/* FindGroupBlock */
void GetGroupDescriptor(int fd, struct ext2_group_desc *group_des)
{
    /* Move the fd to the beggining of the group descriptor - past the boot
    block and the super block: */
    lseek(fd, BLOCK_OFFSET(2), SEEK_SET);
    read(fd, group_des, sizeof(*group_des)); /* read super-block */
}

void InodeInfo(struct ext2_inode *ret_inode)
{
    int i = 0;
    for (i = 0; i < EXT2_N_BLOCKS; i++)
    {
        if (i < EXT2_NDIR_BLOCKS) /* direct blocks */
        {
            printf("Block %2u : %u\n", i, ret_inode->i_block[i]);
        }
        else if (i == EXT2_IND_BLOCK) /* single indirect block */
        {
            printf("Single   : %u\n", ret_inode->i_block[i]);
        }
        else if (i == EXT2_DIND_BLOCK) /* double indirect block */
        {
            printf("Double   : %u\n", ret_inode->i_block[i]);
        }
        else if (i == EXT2_TIND_BLOCK) /* triple indirect block */
        {
            printf("Triple   : %u\n", ret_inode->i_block[i]);
        }
    }
}

void ReadInode(int fd,
               const struct ext2_group_desc *group_descriptor,
               int inode_number,
               struct ext2_inode *ret_inode)
{
    lseek(fd, BLOCK_OFFSET(group_descriptor->bg_inode_table) + (inode_number - 1) * sizeof(struct ext2_inode), SEEK_SET);
    /*lseek(fd, (BLOCK_SIZE + BLOCK_SIZE + sizeof(*group_descriptor) + sizeof(struct ext2_inode)), SEEK_SET);*/
    read(fd, ret_inode, sizeof(struct ext2_inode));

    printf("inode information:\n");
    printf("the i_mode of inode %d is: %d\n", inode_number, ret_inode->i_mode);
    printf("the size of inode %d is: %d\n", inode_number, ret_inode->i_size);
    printf("the i_block of inode %d is: %ls\n\n\n", inode_number, ret_inode->i_block);

    InodeInfo(ret_inode);
}

int FindFileInDir(int fd, const struct ext2_group_desc *group_descriptor,
                  const struct ext2_inode *inode, const char *file_name_to_search,
                  struct ext2_inode *ret_inode)
{

    void *block;
    if (S_ISDIR(inode->i_mode))
    {
        struct ext2_dir_entry_2 *entry;

        unsigned int size = 0;

        if ((block = malloc(BLOCK_SIZE)) == NULL)
        {
            fprintf(stderr, "Memory error\n");
            close(fd);
            exit(1);
        }

        for (int i = 0; i < inode->i_blocks; i++)
        {
            lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
            read(fd, block, BLOCK_SIZE);

            entry = (struct ext2_dir_entry_2 *)block;

            while ((size < inode->i_size) && entry->inode)
            {
                char file_name[EXT2_NAME_LEN + 1];
                memcpy(file_name, entry->name, entry->name_len);
                file_name[entry->name_len] = '\0';
                if (strcmp(file_name, file_name_to_search) == 0)
                {
                    ReadInode(fd, group_descriptor, entry->inode, ret_inode);
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

void print_file(int fd,
                struct ext2_inode *inode,
                int level /* = 0 recursive call support*/)
{
    char buf[BLOCK_SIZE] = {'\0'};
    int int_buf[BLOCK_SIZE / sizeof(int)] = {0};
    int i = 0;

    for (i = 0; inode->i_block[i] != 0; ++i)
    {
        lseek(fd, inode->i_block[i] * BLOCK_SIZE, SEEK_SET);
        read(fd, buf, BLOCK_SIZE);
        printf("%s", buf);
    }

    if (inode->i_block[12] != 0) /* fetch 1 level of indirect blocks */
    {
        lseek(fd, inode->i_block[12] * BLOCK_SIZE, SEEK_SET);
        read(fd, int_buf, BLOCK_SIZE);

        for (i = 0; int_buf[i] != 0; ++i)
        {
            lseek(fd, int_buf[i] * BLOCK_SIZE, SEEK_SET);
            read(fd, buf, BLOCK_SIZE);
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

        if ((block = malloc(BLOCK_SIZE)) == NULL)
        { /* allocate memory for the data block */
            fprintf(stderr, "Memory error\n");
            close(fd);
            exit(1);
        }

        for (size_t i = 0; i < inode->i_blocks; i++)
        {
            lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
            read(fd, block, BLOCK_SIZE);

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

    ReadInode(fd, group, 2, &inode);

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
            print_file(fd, &f_inode, 1);
    }
    else
    {
        printf("File Not Found!\n");
    }
}
/*
void SuperBlockTest()
{
    int fd = open("/dev/ram0", O_RDONLY);
    struct ext2_super_block *super_block =
        (struct ext2_super_block *)malloc(sizeof(struct ext2_super_block));
    struct ext2_group_desc *group_descriptor =
        (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc));
    struct ext2_inode *inode =
        (struct ext2_inode *)malloc(sizeof(struct ext2_inode));
    unsigned char *bitmap = (unsigned char *)malloc(BLOCK_SIZE);
    unsigned int inodes_per_block = 0;
    unsigned int itable_size = 0;

    printf("\n***** superblock test *****\n\n");

    if (fd < 0)
    {
        perror("can't open file");
    }

    GetSuperBlock(fd, super_block);
    GetGroupDescriptor(fd, group_descriptor);

    ReadInode(fd, group_descriptor, 2, inode);
    /*search_directory_by_path(fd, GetGroupDescriptor, inode, , ret_inode);
*/
/* reading the block bitmap :
lseek(fd, BLOCK_OFFSET(group_descriptor->bg_block_bitmap), SEEK_SET);
read(fd, bitmap, BLOCK_SIZE);

read_dir(fd, inode, group_descriptor);
print_file(fd, inode, 96);*/

/* figuring out how many blocks are occupied by the inode table: 
inodes_per_block = BLOCK_SIZE / sizeof(struct ext2_inode);*/
/* size in blocks of the inode table 
itable_size = super_block->s_inodes_per_group / inodes_per_block;
*/
/* The offset of the inode to read is calculated by adding together
    the absolute offset of the inode table and the distance of the desired
 /*
printf("inodes count: %d\n", super_block->s_inodes_count);
printf("blocks count: %d\n", super_block->s_blocks_count);
printf("free inodes count: %d\n", super_block->s_free_inodes_count);
printf("free blocks count: %d\n", super_block->s_free_blocks_count);
printf("currently in use inodes count: %d\n",
       super_block->s_inodes_count - super_block->s_free_inodes_count);
printf("currently in use blocks count: %d\n",
       super_block->s_blocks_count - super_block->s_free_blocks_count);
printf("first data block: %d\n", super_block->s_first_data_block);

printf("blocks per group: %d\n", super_block->s_blocks_per_group);
printf("inodes per group: %d\n", super_block->s_inodes_per_group);
printf("inodes per block: %d\n\n", inodes_per_block);
printf("inodes table size (in blocks): %d\n\n", itable_size);

printf("number of block groups on the disk: %d\n", 1 + (super_block->s_blocks_count - 1) / super_block->s_blocks_per_group);

close(fd);
}
*/
