#include "../include/gdt.h"

gdt_entry_t gdt[4];
gdt_ptr_t gdt_ptr;

void init_segment_descriptor(gdt_entry_t *desc, uint32_t base, uint32_t limit,
			     uint8_t type)
{
	if (limit <= 65536) {
		desc->limitLow = limit & 0xFFFF;
		desc->limitHighAndFlags = (limit >> 16) & 0xFF;
	} else {
		if ((limit & 0xFFF) != 0xFFF)
			limit = (limit >> 12) - 1;
		else
			limit = limit >> 12;

		desc->limitLow = limit & 0xFFFF;
		desc->limitHighAndFlags = ((limit >> 16) & 0xF) | 0xC0;
	}

	desc->baseLow = base & 0xFFFF;
	desc->baseMid = (base >> 16) & 0xFF;
	desc->baseHigh = (base >> 24) & 0xFF;

	desc->type = type;
}

void create_gdt()
{
	init_segment_descriptor(&gdt[0], 0, 0, 0);
	init_segment_descriptor(&gdt[1], 0, 0, 0);
	init_segment_descriptor(&gdt[2], 0, 64 * 1024 * 1024, 0x9A);
	init_segment_descriptor(&gdt[3], 0, 64 * 1024 * 1024, 0x92);

	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = (uint32_t)&gdt;
}

void gdt_init()
{
	create_gdt();

	asm volatile("lgdt (%0)" : : "m"(gdt_ptr));
}
