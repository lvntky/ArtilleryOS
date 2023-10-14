#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>
#include "../../include/common.h"
#include "../../include/config.h"
#include "../../descriptor_tables/include/isr.h"

typedef struct page_t {
	uint32_t is_present;
	uint32_t rw;
	uint32_t user;
	uint32_t access;
	uint32_t dirty;
	uint32_t unused;
	uint32_t frame;
} __attribute__((packed)) page_t;

typedef struct page_table_t {
	page_t page_table[ARTILLERYOS_PAGE_SIZE];
} __attribute__((packed)) page_table_t;

typedef struct page_directory_t {
	page_table_t *tables[ARTILLERYOS_PAGE_SIZE];
	uint32_t physical[ARTILLERYOS_PAGE_SIZE];
	uint32_t physical_address;
} __attribute__((packed)) page_directory_t;

void paging_init();
void switch_page_directory(page_directory_t *);
page_t *get_page(uint32_t, int, page_directory_t *);

// Page fault hanfler for ISR
void page_fault(register_t);

#endif