#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>
#include "memory_util.h"
#include "config.h"
#include "tty.h"

typedef struct idt_t {
	int16_t offset_1; // Offset bits 0 - 15
	uint16_t selector; // Selector thats in our GDT
	uint8_t zero; // Does nothing, unused set to zero
	uint8_t type_attr; // Descriptor type and attributes
	uint16_t offset_2; // Offset bits 16-31
} __attribute__((packed)) idt_t;

typedef struct idt_ptr_t {
	uint16_t limit; // Size of descriptor table -1
	uint32_t base; // Base address of the start of the interrupt descriptor
} __attribute__((packed)) idt_ptr_t;

void idt_init();

#endif