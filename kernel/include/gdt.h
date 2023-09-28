#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../libc/stdio.h"
#include "../libc/string.h"

#define GDTBASE 0x00000800

typedef struct gdt_entry_t {
	uint16_t lim0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t acces;
	uint8_t lim16_19 : 4;
	uint8_t other : 4;
	uint8_t base24_31;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void init_gdt_desc(uint32_t, uint32_t, uint8_t, uint8_t, gdt_entry_t *);
void gdt_init();

#endif