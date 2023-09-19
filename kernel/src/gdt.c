#include "../include/gdt.h"
#include "../libc/stdio.h"

void encode_gdt_entry(gdt_entry_t *entry, uint32_t base, uint32_t limit,
		      uint8_t access, uint8_t granularity)
{
	entry->limit_low = limit & 0xFFFF;
	entry->base_low = base & 0xFFFF;
	entry->base_middle = (base >> 16) & 0xFF;
	entry->access = access;
	entry->granularity = (granularity << 4) | ((limit >> 16) & 0x0F);
	entry->base_high = (base >> 24) & 0xFF;
}

void init_gdt()
{
	gdt_entry_t gdt_entries[3];
	gdt_ptr_t gdt_ptr;

	encode_gdt_entry(&gdt_entries[0], 0, 0, 0, 0); // Null segment
	encode_gdt_entry(&gdt_entries[1], 0, 0xFFFFF, 0x9A,
			 0xCF); // Code segment
	encode_gdt_entry(&gdt_entries[2], 0, 0xFFFFF, 0x92,
			 0xCF); // Data segment

	gdt_ptr.limit = sizeof(gdt_entries) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries[0];

	printf("\n***GDT CHECK*** ");
	printf("\nBefore initializing GDT:\n");

	// Print the values of segment registers
	uint16_t cs, ds, es, fs, gs;
	__asm__ __volatile__("mov %%cs, %0" : "=r"(cs));
	__asm__ __volatile__("mov %%ds, %0" : "=r"(ds));
	__asm__ __volatile__("mov %%es, %0" : "=r"(es));
	__asm__ __volatile__("mov %%fs, %0" : "=r"(fs));
	__asm__ __volatile__("mov %%gs, %0" : "=r"(gs));

	printf("CS: 0x%x\nDS: 0x%x\nES: 0x%x\nFS: 0x%x\nGS: 0x%x\n", cs, ds, es,
	       fs, gs);

	__asm__ __volatile__("lgdt %0" : : "m"(gdt_ptr));

	// Load segment registers to reload CS and DS
	__asm__ __volatile__("mov $0x10, %ax;"
			     "mov %ax, %ds;"
			     "mov %ax, %es;"
			     "mov %ax, %fs;"
			     "mov %ax, %gs;"
			     "ljmp $0x08, $reload_cs;"
			     "reload_cs:");

	printf("After initializing GDT:\n");

	// Print the values of segment registers after initialization
	__asm__ __volatile__("mov %%cs, %0" : "=r"(cs));
	__asm__ __volatile__("mov %%ds, %0" : "=r"(ds));
	__asm__ __volatile__("mov %%es, %0" : "=r"(es));
	__asm__ __volatile__("mov %%fs, %0" : "=r"(fs));
	__asm__ __volatile__("mov %%gs, %0" : "=r"(gs));

	printf("CS: 0x%x\nDS: 0x%x\nES: 0x%x\nFS: 0x%x\nGS: 0x%x\n", cs, ds, es,
	       fs, gs);
}
