/**
 * @file gdt.h
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief global descriptor table high level implementation
 * @version 0.1
 * @date 2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>

typedef struct global_descriptor_table {
	uint16_t DataSegmentSelector;
	uint16_t CodeSegmentSelector;
} __attribute__((packed)) global_descriptor_table;

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

void encode_gdt_entry(gdt_entry_t *, uint32_t, uint32_t, uint8_t, uint8_t);
void init_gdt();
