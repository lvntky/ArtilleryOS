#ifndef _TEMPFS_INITRD_H_
#define _TEMPFS_INITRD_H_

#include <stdint.h>
#include "tempfs.h"
#include "../../../memory/include/kernel_heap.h"
#include "../../../libc/include/string.h"
#include "../../../include/qemu_debug.h"

typedef struct {
	uint32_t nfiles;
} initrd_header_t;

typedef struct {
	unsigned magic;
	char name[64];
	uint32_t offset; // Offset in the initrd that the file starts.
	uint32_t length; // Length of the file.
} initrd_file_header_t;

tempfs_node_t *tempfs_initrd_init(uint32_t location);

#endif