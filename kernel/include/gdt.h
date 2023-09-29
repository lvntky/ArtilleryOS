#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../libc/stdio.h"
#include "../libc/string.h"

#define GDT_SIZE 5

typedef struct gdt_entry_t {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

static void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);
void gdt_init();

#endif