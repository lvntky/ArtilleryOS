#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <stdint.h>
#include "../include/config.h"
#include "../libc/string.h"
#include "../libc/stdio.h"

typedef struct idt_entry_t {
	uint16_t base_low;
	uint16_t kernel_segment_selector;
	uint8_t zero; // always 0
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
	uint16_t base;
	uint32_t limit;
} __attribute__((packed)) idt_ptr_t;

void idt_init();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

// These extern directives let us access the addresses of ASM ISR handlers.
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr31();

#endif