#include "../include/gdt.h"

gdt_entry_t gdt[5];
gdt_ptr_t gp;

extern void asm_gdt_flush();

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access,
		  uint8_t gran)
{
	/* Setup the descriptor base address */
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_init()
{
	/* Setup the GDT pointer and limit */
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = (uint32_t)&gdt;

	/* NULL descriptor */
	gdt_set_gate(0, 0, 0, 0, 0);

	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	// User code and data segments, only differ in ring number(ring 3)
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	asm_gdt_flush();
	qemu_write_string("%s GDT initialized\n", POSITIVE_OUTPUT);
}