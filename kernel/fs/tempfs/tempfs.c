
#include "./include/tempfs.h"

tempfs_node_t *fs_root = 0;

uint32_t read_fs(tempfs_node_t *node, uint32_t offset, uint32_t size,
		 unsigned char *buffer)
{
	if (node->read != 0)
		return node->read(node, offset, size, buffer);
	else
		return 0;
}

uint32_t write_fs(tempfs_node_t *node, uint32_t offset, uint32_t size,
		  unsigned char *buffer)
{
	if (node->write != 0)
		return node->write(node, offset, size, buffer);
	else
		return 0;
}

void open_fs(tempfs_node_t *node, unsigned char read, unsigned char write)
{
	if (node->open != 0)
		return node->open(node);
}

void close_fs(tempfs_node_t *node)
{
	if (node->close != 0)
		return node->close(node);
}

struct dirent *readdir_fs(tempfs_node_t *node, uint32_t index)
{
	if ((node->flags & 0x7) == FS_DIRECTORY && node->readdir != 0)
		return node->readdir(node, index);
	else
		return 0;
}

tempfs_node_t *finddir_fs(tempfs_node_t *node, char *name)
{
	if ((node->flags & 0x7) == FS_DIRECTORY && node->finddir != 0)
		return node->finddir(node, name);
	else
		return 0;
}
