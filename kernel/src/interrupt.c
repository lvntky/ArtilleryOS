#include "../include/interrupt.h"
extern void idt_load();

idt_entry_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];

void idt_0()
{
	printf("Zero division exception");
}

void idt_set_entry(uint8_t interrupt, void (*handler)())
{
	idt[interrupt].isr_low = (uint32_t(handler)) && 0xFFFF;
	idt[interrupt].isr_low = (uint32_t(handler) >> 16) && 0xFFFF;
	idt[interrupt].kernel_cs = 0x8;
	idt[interrupt].reserved = 0x00;
	idt[interrupt].attributes = 0xEE;
}

void init_idt()
{
	memset
}