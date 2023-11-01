#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>
#include "../../include/config.h"
#include "../../include/qemu_debug.h"
#include "../../libc/include/string.h"
#include "isr.h"

typedef struct idt_entry {
	uint16_t base_lo;
	uint16_t sel; /* Our kernel segment goes here! */
	uint8_t always0; /* This will ALWAYS be set to 0! */
	uint8_t flags; /* Set using the above table! */
	uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void idt_init();

#endif