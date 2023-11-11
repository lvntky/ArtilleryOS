#include "../include/paging.h"

extern void pdt_set(uint32_t); // comes from paging_enable.asm

void create_pdt_entry(page_directory_entry_t *pdt, uint32_t n, uint32_t addr,
		      uint8_t ps)
{
	pdt[n].low_addr = ((addr >> 12) & 0xF) << 4;
	pdt[n].high_addr = ((addr >> 16) & 0xFFFF);

	pdt[n].config = ((ps && 0x01) << 7) | (0x01 << 3) | (0x01 << 1) | 0x01;
}

void create_pt_entry(page_table_entry_t *pt, uint32_t n, uint32_t addr)
{
	pt[n].middle = ((addr >> 12) & 0xF) << 4;
	pt[n].high_addr = ((addr >> 16) & 0xFFFF);

	pt[n].config = (0x01 << 3) | (0x01 << 1) | 0x01;
}

void paging_init(uint32_t boot_page_directory)
{
	uint32_t i, cr3;
	page_directory_entry_t *pdt =
		(page_directory_entry_t *)boot_page_directory;

	create_pdt_entry(pdt, 1, 0x10000000, PS_4MB);

	cr3 = VIRTUAL_TO_PHYSICAL(boot_page_directory) | (0x01 << 3);
	pdt_set(cr3);

	qemu_write_string("%s Paging initialized\n", POSITIVE_OUTPUT);
	qemu_write_string("%s Boot page directory: 0x%x\n", INFORMATION_OUTPUT,
			  (uint32_t)pdt);
	qemu_write_string("%s Present pages:\n", INFORMATION_OUTPUT);

	for (i = 0; i < NUM_ENTRIES; ++i) {
		if (IS_ENTRY_PRESENT(pdt + i)) {
			qemu_write_string("%d: 0x%x\n", i, pdt[i]);
		}
	}

	UNUSED_ARGUMENT(create_pt_entry);
}
