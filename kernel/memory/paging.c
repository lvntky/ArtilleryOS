#include "include/paging.h"
#include "include/kheap.h"

void paging_handler(register_t *reg)
{
	printf("paging exception");
}

// The kernel's page directory
page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;
uint32_t *frames;
uint32_t nframes;
extern uint32_t placement_addr;

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static uint32_t first_frame()
{
	uint32_t i, j;
	for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if (frames[i] != 0xFFFFFFFF) {
			for (j = 0; j < 32; j++) {
				uint32_t toTest = 0x1 << j;
				if (!(frames[i] & toTest)) {
					return i * 32 + j;
				}
			}
		}
	}
	return (uint32_t)-1;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
	if (page->frame != 0) {
		return;
	} else {
		uint32_t idx = first_frame();
		if (idx == (uint32_t)-1) {
			// PANIC! no free frames!!

			panic("No frames left!", "paging.c");
			// Handle this case accordingly
		}
		set_frame(idx * 0x1000);
		page->present = 1;
		page->rw = (is_writeable) ? 1 : 0;
		page->user = (is_kernel) ? 0 : 1;
		page->frame = idx;
	}
}

void free_frame(page_t *page)
{
	uint32_t frame;
	if (!(frame = page->frame)) {
		return;
	} else {
		clear_frame(frame * 0x1000);
		page->frame = 0;
	}
}

void paging_init()
{
	uint32_t mem_end_page = 0x1000000;
	nframes = mem_end_page / 0x1000;
	frames = (uint32_t *)kmalloc_vanilla(INDEX_FROM_BIT(nframes));

	kernel_directory =
		(page_directory_t *)kmalloc_aligned(sizeof(page_directory_t));
	current_directory = kernel_directory;

	int i = 0;
	while (i < placement_addr) {
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}
	// Before we enable paging, we must register our page fault handler.
	isr_install_handler(14, paging_handler);

	// Now, enable paging!
	switch_page_directory(kernel_directory);
	// printf("[INIT] Paging initialized successfully!\n");
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	asm volatile("mov %0, %%cr3" ::"r"(&dir->tablesPhysical));
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	asm volatile("mov %0, %%cr0" ::"r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir)
{
	address /= 0x1000;
	uint32_t table_idx = address / 1024;
	if (dir->tables[table_idx]) {
		return &dir->tables[table_idx]->pages[address % 1024];
	} else if (make) {
		uint32_t tmp;
		dir->tables[table_idx] = (page_table_t *)
			kmalloc_aligned_and_return_physical_addr(
				sizeof(page_table_t), &tmp);
		dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
		return &dir->tables[table_idx]->pages[address % 1024];
	} else {
		return 0;
	}
}