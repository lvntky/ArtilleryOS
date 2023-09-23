#include "idt.h"

extern void idt_load(idt_ptr_t *ptr); // ist.asm
extern void int21h();
extern void no_interrupt();

idt_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t idt_ptr;

void int21h_handler()
{
	printf("\nKeyboard pressed!\n");
	outb(0x20, 0x20);
}

void no_interrupt_handler()
{
	outb(0x20, 0x20);
}

void idt_0()
{
	printf("INTERRUPT_0: Division by zero!\n");
}

void idt_set(int interrupt_no, void *handler)
{
	idt_t *desc = &idt[interrupt_no];
	desc->offset_1 = (uint32_t)handler & 0x0000ffff;
	desc->selector = 0x8; // code sector
	desc->zero = 0x00;
	desc->type_attr = 0xEE;
	desc->offset_2 = (uint32_t)handler >> 16;
}

void idt_init()
{
	memset(idt, 0, sizeof(idt));
	idt_ptr.limit = (sizeof(idt)) - 1;
	idt_ptr.base = (uint32_t)idt;

	for (int i = 0; i < ARTILLERYOS_MAX_INTERRUPT_SIZE; i++) {
		idt_set(i, no_interrupt_handler);
	}

	idt_set(0, idt_0);
	idt_set(0x21, int21h);

	idt_load(&idt_ptr);
}