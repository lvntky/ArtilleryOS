#ifndef _IDT_H
#define _IDT_H

#include "../libc/string.h"
#include "../include/config.h"
#include "isr.h"

typedef struct idt_entry_t {
	unsigned short base_lo;
	unsigned short sel; /* Our kernel segment goes here! */
	unsigned char always0; /* This will ALWAYS be set to 0! */
	unsigned char flags; /* Set using the above table! */
	unsigned short base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
		  unsigned char flags);
void idt_init();

#endif