#include "../include/gdt.h"

gdt_entry_t gdt[7];
gdt_ptr_t gdt_ptr;

void init_gdt_desc(uint32_t base, uint32_t limit, uint8_t access, uint8_t other,
		   gdt_entry_t *desc)
{
	desc->lim0_15 = (limit & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = access;
	desc->lim16_19 = (limit & 0xf0000) >> 16;
	desc->other = (other & 0xf);
	desc->base24_31 = (base & 0xff000000) >> 24;
	return;
}

void gdt_init()
{
	/* initialize gdt segments */
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, &gdt[0]);
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &gdt[1]); /* code */
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &gdt[2]); /* data */
	init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &gdt[3]); /* stack */

	init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &gdt[4]); /* ucode */
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &gdt[5]); /* udata */
	init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &gdt[6]); /* ustack */

	/* initialize the gdt_ptr structure */
	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = GDTBASE;

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
            ljmp $0x08, $next    \n \
            next:        \n");
}