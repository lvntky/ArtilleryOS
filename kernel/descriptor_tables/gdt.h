#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../include/config.h"

typedef struct gdt_entry_t {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed)) gdt_entry_t;

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
typedef struct gdt_ptr_t {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_init();

#endif