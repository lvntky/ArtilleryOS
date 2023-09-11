/**
* Interrupt Descriptor Table
*/
#ifdef __IDT_H__
#define __IDT_H__

#include <stdint.h>

struct Idt_desc {
	uint16_t offset_1; // offset 0-15 -> lower bits
	uint16_t selector // selector in GDT
		uint8_t zero;
	uint8_t type_attribute; // descriptor type and attribute
	uint16_t offset_2; // offset 16-31 -> higher bits
} __attribute__((packed));

struct Idtr {
	uint16_t limit; // size of descriptor table - 1
	uint32_t base; // pointer the start of the idt
} __attribute__((packed));

void idt_init(void);
void idt_set(int, void *) void idt_zero(void);

#endif