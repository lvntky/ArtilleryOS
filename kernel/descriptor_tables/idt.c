#include "./include/idt.h"

extern void _idt_load();

idt_entry_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t _idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
		  unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}

/* Installs the IDT */
void idt_init()
{
	/* Sets the special IDT pointer up, just like in 'gdt.c' */
	_idtp.limit =
		(sizeof(idt_entry_t) * ARTILLERYOS_MAX_INTERRUPT_SIZE) - 1;
	_idtp.base = (unsigned int)&idt;

	/* Clear out the entire IDT, initializing it to zeros */
	memset(&idt, 0, sizeof(idt_entry_t) * ARTILLERYOS_MAX_INTERRUPT_SIZE);

	isrs_install();
	irqs_install();

	/* Points the processor's internal register to the new IDT */
	_idt_load();
}
