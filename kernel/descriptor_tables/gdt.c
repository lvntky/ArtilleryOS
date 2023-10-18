#include "./include/gdt.h"

extern void _gdt_flush(); // gdt_flush.asm

gdt_entry_t gdt[ARTILLERYOS_GDT_SIZE];
gdt_ptr_t _gp;

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
		  unsigned char access, unsigned char gran)
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
	_gp.limit = (sizeof(gdt_entry_t) * ARTILLERYOS_GDT_SIZE) - 1;
	_gp.base = (unsigned int)&gdt;

	/* Our NULL descriptor */
	gdt_set_gate(0, 0, 0, 0, 0);

	/* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* Flush out the old GDT and install the new changes! */
	_gdt_flush();
	printf("[INIT] GDT initialized successfully!\n");
}