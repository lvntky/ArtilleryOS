#ifndef _PAGING_H_
#define _PAGING_H_

#include <stdint.h>
#include "../../include/qemu_debug.h"
#include "../../libc/include/string.h"

typedef struct page_directory_entry {
	uint8_t config;
	uint8_t low_addr; /* only the highest 4 bits are used */
	uint16_t high_addr;
} __attribute__((packed)) page_directory_entry_t;

typedef struct page_table_entry {
	uint8_t config;
	uint8_t middle; /* only the highest 4 bits and the lowest bit are used */
	uint16_t high_addr;
} __attribute__((packed)) page_table_entry_t;

#define NUM_ENTRIES 1024
#define PDT_SIZE NUM_ENTRIES * sizeof(page_directory_entry_t)
#define PT_SIZE NUM_ENTRIES * sizeof(page_table_entry_t)

#define VIRTUAL_TO_PDT_IDX(a) ((a >> 20) & 0x3FF)

#define PS_4KB 0x00
#define PS_4MB 0x01

#define IS_ENTRY_PRESENT(e) ((e)->config && 0x01)

void paging_init(uint32_t);

#endif