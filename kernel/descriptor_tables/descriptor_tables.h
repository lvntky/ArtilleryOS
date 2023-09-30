#ifndef _DESCRIPTOR_TABLES_H
#define _DESCRIPTOR_TABLES_H

#include <stdint.h>
#include "../include/config.h"
#include "../libc/string.h"

/** GDT */
typedef struct gdt_entry_t {
	uint16_t limit_low;
	uint16_t base_low; // lower 16 bits of base
	uint8_t base_middle; // the next 8 bits
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high; // the last 8 bits
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;
/** GDT END*/

/** IDT */
typedef struct idt_entry_t {
	uint16_t base_lo; // The lower 16 bits of the address to jump to when this interrupt fires.
	uint16_t sel; // Kernel segment selector.
	uint8_t always0; // This must always be zero.
	uint8_t flags; // More flags. See documentation.
	uint16_t base_hi; // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
	uint32_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;

// external ASM ISR handlers
extern void isr0;
extern void isr1;
extern void isr2;
extern void isr3;
extern void isr4;
extern void isr5;
extern void isr6;
extern void isr7;
extern void isr8;
extern void isr9;
extern void isr10;
extern void isr11;
extern void isr12;
extern void isr13;
extern void isr14;
extern void isr15;
extern void isr16;
extern void isr17;
extern void isr18;
extern void isr19;
extern void isr20;
extern void isr21;
extern void isr22;
extern void isr23;
extern void isr24;
extern void isr25;
extern void isr26;
extern void isr27;
extern void isr28;
extern void isr29;
extern void isr30;
extern void isr31;
/** IDT END */

// GDT + IDT
void descriptor_tables_init();

#endif