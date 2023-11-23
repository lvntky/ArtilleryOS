#ifndef _TEMPFS_H_
#define _TEMPFS_H_

#define MAX_FILE_NAME_LEN 128

#include <stdint.h>

typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32_t);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name); 

typedef struct tempfs_node
{
    char file_name[MAX_FILE_NAME_LEN];
    uint32_t flags;
    read_type_t read;   // These typedefs are just function pointers.
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir; // Returns the n'th child of a directory.
    finddir_type_t finddir; // Try to find a child in a directory by name.
} __attribute__((packef)) tempfs_node_t;



#endif