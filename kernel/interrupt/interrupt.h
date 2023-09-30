#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <stdint.h>
#include "../include/config.h"
#include "../libc/string.h"
#include "../libc/stdio.h"
#include "../include/gdt.h"

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
#endif