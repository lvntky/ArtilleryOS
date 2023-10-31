#ifndef _IDT_H_
#define _IDT_H_

#define NUM_IDT_ENTRIES 256
#include <stdint.h>
#include "isr.h"
#include "../../libc/include/string.h"
#include "../../driver/include/pic.h"
#include "../../include/qemu_debug.h"

typedef struct idt_entry {
	uint16_t base_lo;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

// Idt functions
void idt_init();
void idt_set_entry(int index, uint32_t base, uint16_t sel, uint8_t ring);

#endif
