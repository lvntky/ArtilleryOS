#include "idt.h"

extern void idt_load(idt_ptr_t *ptr); // ist.asm

idt_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t idt_ptr;

void idt_0()
{
	printf("INTERRUPT_0: Division by zero!\n");
	__asm__ volatile("hlt;");
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

	idt_set(0, idt_0);

	idt_load(&idt_ptr);
}