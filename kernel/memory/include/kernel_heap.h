#ifndef _KERNEL_HEAP_H_
#define _KERNEL_HEAP_H_

#include <stdint.h>
#include <stddef.h>
#include "../../include/qemu_debug.h"

typedef double align;
union header {
	struct {
		union header *next;
		size_t size; /* size in "number of header units" */
	} s;
	align x; /* force alignment of blocks, never use */
};

typedef union header header_t;

void kmalloc_init(uint32_t, size_t);
void *kmalloc(size_t);
void kfree(void *);

#endif