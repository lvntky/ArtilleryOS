#ifndef _GDT_H
#define _GDT_H

#define NUM_DESCRIPTORS 8

#include <stdint.h>
#include "../../include/config.h"
#include "../../include/qemu_debug.h"

#define GDT_SEGMENT_SIZE 3
typedef struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;
typedef struct gdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

/* Our GDT, with 3 entries, and finally our special GDT pointer */
void gdt_init();
void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

#endif