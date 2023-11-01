#include "../include/idt.h"

idt_entry_t idt[256];
idt_ptr_t idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void asm_idt_load();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	/* The interrupt routine's base address */
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	/* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}

void idt_init()
{
	/* Sets the special IDT pointer up, just like in 'gdt.c' */
	idtp.limit = (sizeof(idt_entry_t) * 256) - 1;
	idtp.base = (uint32_t)&idt;

	/* Clear out the entire IDT, initializing it to zeros */
	memset(&idt, 0, sizeof(idt_entry_t) * 256);

	/* Add any new ISRs to the IDT here using idt_set_gate */
	// kernel level
	idt_set_gate(0, (unsigned)exception0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned)exception1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)exception2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)exception3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)exception4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)exception5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)exception6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)exception7, 0x08, 0x8E);

	idt_set_gate(8, (unsigned)exception8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)exception9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)exception10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)exception11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)exception12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)exception13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)exception14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)exception15, 0x08, 0x8E);

	idt_set_gate(16, (unsigned)exception16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)exception17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)exception18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)exception19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)exception20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)exception21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)exception22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)exception23, 0x08, 0x8E);

	idt_set_gate(24, (unsigned)exception24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)exception25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)exception26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)exception27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)exception28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)exception29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned)exception30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned)exception31, 0x08, 0x8E);
	/* Points the processor's internal register to the new IDT */
	// interrupts
	pic_init();
	idt_set_gate(32, (unsigned)interrupt0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)interrupt1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)interrupt2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)interrupt3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)interrupt4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)interrupt5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)interrupt6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)interrupt7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)interrupt8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)interrupt9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)interrupt10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)interrupt11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)interrupt12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)interrupt13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)interrupt14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)interrupt15, 0x08, 0x8E);

	asm_idt_load();
	__asm__ __volatile__("sti");

	qemu_write_string("%s IDT initialized\n", POSITIVE_OUTPUT);
}