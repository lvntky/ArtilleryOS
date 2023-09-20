#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <stdint.h>
#include "../libc/stdio.h"

#define ARTILLERYOS_MAX_INTERRUPT_SIZE 256
typedef struct idt_entry_t {
	uint16_t isr_low; // The lower 16 bits of the ISR's address
	uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t reserved; // Set to zero
	uint8_t attributes; // Type and attributes; see the IDT page
	uint16_t isr_high; // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_descriptor(uint8_t, void *, uint8_t);
void init_idt();
void exception_handler(void);

#endif
