#ifndef _TFS_INODE_H_
#define _TFS_INODE_H_

#define MAX_FILE_LEN 256
#define FILETYPE_REG 0
#define FILETYPE_DIR 1

#include <stdint.h>

struct tfs_inode
{
    uint32_t type;
    uint32_t location;
    uint32_t size;
} __attribute__((packed)) tfs_inode_t;

typedef struct tfs_direntry
{
    char name[MAX_FILE_LEN];
    uint32_t location;
} __attribute__((packed)) tfs_direntry_t;



#endif