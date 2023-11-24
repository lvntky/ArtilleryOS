
#ifndef FS_H
#define FS_H

#define FS_FILE 0x01
#define FS_DIRECTORY 0x02
#define FS_CHARDEVICE 0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE 0x05
#define FS_SYMLINK 0x06
#define FS_MOUNTPOINT 0x08 // Is the file an active mountpoint?

#include <stdint.h>

struct tempfs_node;

typedef uint32_t (*read_type_t)(struct tempfs_node *, uint32_t, uint32_t,
				unsigned char *);
typedef uint32_t (*write_type_t)(struct tempfs_node *, uint32_t, uint32_t,
				 unsigned char *);
typedef void (*open_type_t)(struct tempfs_node *);
typedef void (*close_type_t)(struct tempfs_node *);
typedef struct dirent *(*readdir_type_t)(struct tempfs_node *, uint32_t);
typedef struct tempfs_node *(*finddir_type_t)(struct tempfs_node *, char *name);

typedef struct tempfs_node {
	char name[128]; // The filename.
	uint32_t mask; // The permissions mask.
	uint32_t uid; // The owning user.
	uint32_t gid; // The owning group.
	uint32_t flags; // Includes the node type. See #defines above.
	uint32_t inode; // This is device-specific - provides a way for a filesystem to identify files.
	uint32_t length; // Size of the file, in bytes.
	uint32_t impl; // An implementation-defined number.
	read_type_t read;
	write_type_t write;
	open_type_t open;
	close_type_t close;
	readdir_type_t readdir;
	finddir_type_t finddir;
	struct tempfs_node *ptr; // Used by mountpoints and symlinks.
} tempfs_node_t;

struct dirent {
	char name[128];
	uint32_t ino;
};

extern tempfs_node_t *fs_root;

uint32_t read_fs(tempfs_node_t *node, uint32_t offset, uint32_t size,
		 unsigned char *buffer);
uint32_t write_fs(tempfs_node_t *node, uint32_t offset, uint32_t size,
		  unsigned char *buffer);
void open_fs(tempfs_node_t *node, unsigned char read, unsigned char write);
void close_fs(tempfs_node_t *node);
struct dirent *readdir_fs(tempfs_node_t *node, uint32_t index);
tempfs_node_t *finddir_fs(tempfs_node_t *node, char *name);

#endif
