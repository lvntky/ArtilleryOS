#include "../include/paging.h"

extern void pdt_set(uint32_t); // comes from paging_enable.asm

void create_pdt_entry(page_directory_entry_t *pdt, uint32_t n,
		      page_table_entry_t *pte)
{
	uint32_t addr = (uint32_t)pte;

	pdt[n].low_addr = ((addr >> 12) & 0xF) << 4;
	pdt[n].high_addr = ((addr >> 16) & 0xFFFF);

	pdt[n].config = (0x01 << 3) | (0x01 << 1) | 0x01;
}

void create_pt_entry(page_table_entry_t *pt, uint32_t n, uint32_t addr)
{
	pt[n].middle = ((addr >> 12) & 0xF) << 4;
	pt[n].high_addr = ((addr >> 16) & 0xFFFF);

	pt[n].config = (0x01 << 3) | (0x01 << 1) | 0x01;
}

void paging_init(uint32_t end_of_kernel)
{
	uint32_t i, cr3 = 0;
	page_directory_entry_t *pdt = (page_directory_entry_t *)end_of_kernel;
	page_table_entry_t *pt =
		(page_table_entry_t *)(end_of_kernel + PDT_SIZE);

	memset(pdt, 0, PDT_SIZE);
	memset(pt, 0, PT_SIZE);

	for (i = 0; i < 1024; ++i) {
		create_pt_entry(pt, i, 0x00000000 + i * 4096);
	}

	create_pdt_entry(pdt, 0, pt);
	qemu_write_string("%s Paging initialized\n", POSITIVE_OUTPUT);

	qemu_write_string("\n%s %s START\n", DEBUG_OUTPUT, PAGE_OUTPUT);
	qemu_write_string("%s pdt: 0x%x\n", INFORMATION_OUTPUT, (uint32_t)pdt);
	qemu_write_string("%s pt: 0x%x\n", INFORMATION_OUTPUT, (uint32_t)pt);
	qemu_write_string("%s pdt[0].config 0x%x\n", INFORMATION_OUTPUT,
			  pdt[0].config);
	qemu_write_string("%s pdt[0].low_addr 0x%x\n", INFORMATION_OUTPUT,
			  pdt[0].low_addr);
	qemu_write_string("%s pdt[0].high_addr 0x%x\n", INFORMATION_OUTPUT,
			  pdt[0].high_addr);
	qemu_write_string("%s %s END\n\n", DEBUG_OUTPUT, PAGE_OUTPUT);

	cr3 = ((uint32_t)pdt & 0xFFFFF000) | (0x01 << 3);
	pdt_set(cr3);
}
