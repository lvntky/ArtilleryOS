#include "../include/gdt.h"

gdt_entry_t gdt[GDT_SIZE];
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit,
			 uint8_t access, uint8_t gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = (limit >> 16) & 0x0F;

	gdt[num].granularity |= gran & 0xF0;
	gdt[num].access = access;
}

void gdt_init()
{
	gdt_ptr.limit = (sizeof(gdt) * GDT_SIZE) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	/* initialize gdt segments */
	gdt_set_gate(0, 0, 0, 0, 0); // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	/* copy the gdt_ptr to its memory area */
	memcpy((char *)gdt_ptr.base, (char *)gdt, gdt_ptr.limit + 1);

	/* load the gdt_ptr registry */
	asm("lgdtl (gdt_ptr)");

	/* initiliaz the segments */
	asm("   movw $0x10, %ax    \n \
            movw %ax, %ds    \n \
            movw %ax, %es    \n \
            movw %ax, %fs    \n \
            movw %ax, %gs    \n \
			movw %ax, %ss    \n \
            ljmp $0x08, $next    \n \
            next:        \n");
}