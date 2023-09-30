#include "../include/gdt.h"

void load_gdt(struct global_descriptor_table *gdt)
{
	uint32_t i[2];
	i[1] = (uint32_t)gdt;
	i[0] = sizeof(struct global_descriptor_table) << 16;
	asm volatile("lgdt (%0)" : : "p"(((uint8_t *)i) + 2));
}

uint16_t data_segment_selector(struct global_descriptor_table *gdt)
{
	return (uint8_t *)&gdt->data_segment_selector - (uint8_t *)gdt;
}

uint16_t code_segment_selector(struct global_descriptor_table *gdt)
{
	return (uint8_t *)&gdt->code_segment_selector - (uint8_t *)gdt;
}

global_descriptor_table gdt;
void gdt_init()
{
	// Adjusted initialization with a 64 MB limit
	gdt.code_segment_selector = (struct segment_descriptor){
		0, 64 * 1024 / 8, 0, 0x9A, 0xC, 0
	};
	gdt.data_segment_selector = (struct segment_descriptor){
		0, 64 * 1024 / 8, 0, 0x92, 0xC, 0
	};

	load_gdt(&gdt);

	printf("\n============================\n");
	printf("GDT INFO\n");
	printf("\nCode Segment: 0x%x\n", get_code_segment());
	printf("Data Segment: 0x%x\n", get_data_segment());
	printf("============================\n");
}

uint16_t get_code_segment()
{
	return code_segment_selector(&gdt);
}

uint16_t get_data_segment()
{
	return data_segment_selector(&gdt);
}