#include "descriptor_tables.h"

/** GDT */

// need to access from ASM code
extern void gdt_flush(uint32_t);

// internal functions
static void gdt_init();

gdt_entry_t gdt_entries[ARTILLERYOS_GDT_SIZE];
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit,
			 uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}
static void gdt_init()
{
	gdt_ptr.limit = (sizeof(gdt_entries) * ARTILLERYOS_GDT_SIZE) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0); // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdt_flush((uint32_t)&gdt_ptr);
}

/** GDT END */

/** IDT */
extern void idt_flush(uint32_t);

static void idt_init();

idt_entry_t idt_entries[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t idt_ptr;

static void idt_set_gate(unsigned char num, unsigned int base,
			 unsigned short sel, unsigned char flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	idt_entries[num].flags = flags /* | 0x60 */;
}

static void idt_init()
{
	idt_ptr.limit =
		(sizeof(idt_entries) * ARTILLERYOS_MAX_INTERRUPT_SIZE) - 1;
	idt_ptr.base = (uint32_t)&idt_entries;

	memset(&idt_entries, 0,
	       (sizeof(idt_entries) * ARTILLERYOS_MAX_INTERRUPT_SIZE));

	//idt_set_gate(0, (unsigned int)isr0, 0x08, 0x8E);
	//idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);

	idt_flush((uint32_t)&idt_ptr);
}

void descriptor_tables_init()
{
	gdt_init();
	idt_init();
}