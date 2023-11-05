#ifndef _PAGING_H_
#define _PAGING_H_

#define PAGING_ENTRY_SIZE 1024
#define KERNEL_BASE_VIRT 0xC0000000

#define PHYS_TO_VIRT(addr) ((addr) + KERNEL_BASE_VIRT)
#define VIRT_TO_PHYS(addr) ((addr)-KERNEL_BASE_VIRT)

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3FF)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3FF)

#include <stdint.h>
#include <stdbool.h>
#include "../../include/qemu_debug.h"
#include "../../descriptor_tables/include/isr.h"

typedef struct directory_entry {
	uint32_t present : 1;
	uint32_t rw : 1;
	uint32_t user : 1;
	uint32_t writethrough : 1;
	uint32_t disable_cache : 1;
	uint32_t accessed : 1;
	uint32_t zero : 1;
	uint32_t large_pages : 1;
	uint32_t unused : 1;
	uint32_t available : 3;
	uint32_t frame : 20;
} __attribute__((packed)) directory_entry_t;

typedef struct page {
	uint32_t present : 1;
	uint32_t rw : 1;
	uint32_t user : 1;
	uint32_t writethrough : 1;
	uint32_t disable_cache : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t zero : 1;
	uint32_t global : 1;
	uint32_t available : 3;
	uint32_t frame : 20;
} __attribute__((packed)) page_t;

typedef struct page_table {
	page_t entries[PAGING_ENTRY_SIZE];
} page_table_t;

typedef struct page_directory {
	directory_entry_t entries[PAGING_ENTRY_SIZE];
} page_directory_t;

#endif