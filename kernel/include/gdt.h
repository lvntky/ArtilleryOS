#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

typedef struct segment_descriptor {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) segment_descriptor;

typedef struct global_descriptor_table {
	struct segment_descriptor null_segment_selector;
	struct segment_descriptor unused_segment_selector;
	struct segment_descriptor code_segment_selector;
	struct segment_descriptor data_segment_selector;
} __attribute__((packed)) global_descriptor_table;

void load_gdt(struct global_descriptor_table *gdt);

uint16_t get_code_segment();
uint16_t get_data_segment();

void gdt_init();

#endif /* GDT_H */
