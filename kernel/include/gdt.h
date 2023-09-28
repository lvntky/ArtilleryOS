#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../libc/stdio.h"

typedef struct gdt_entry_t {
	uint8_t limitLow;
	uint8_t baseLow;
	uint8_t baseMid;
	uint8_t type;
	uint8_t limitHighAndFlags;
	uint8_t baseHigh;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_t {
	uint16_t limit;
	uint8_t base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_init();

#endif