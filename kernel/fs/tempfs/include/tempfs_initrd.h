#ifndef _TEMPFS_INITRD_H_
#define _TEMPFS_INITRD_H_

#include "tempfs.h"
#include "../../../memory/include/kernel_heap.h"
#include "../../../libc/include/string.h"

typedef struct initrd_header {
	uint32_t nfiles; // The number of files in the ramdisk.
} initrd_header_t;

typedef struct {
	uint8_t magic; // Magic number, for error checking.
	char name[ARTILLERY_MAX_FILE_NAME_LEN];
	uint32_t offset; // Offset in the initrd that the file starts.
	uint32_t length; // Length of the file.
} initrd_file_header_t;

tempfs_node_t *tempfs_initrd_init(uint32_t location);

#endif