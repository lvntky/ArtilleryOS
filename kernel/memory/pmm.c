#include "include/pmm.h"

uint32_t *bitmap = (uint32_t *)(&end);
uint8_t *mem_start;
uint32_t total_blocks;
uint32_t bitmap_size;

void print_memory_region()
{
	for (uint32_t i = 0; i < total_blocks; ++i) {
		qemu_write_string("0x%x\n", bitmap[i]);
	}
}

void pmm_init(uint32_t mem_size)
{
	total_blocks = mem_size / BLOCK_SIZE;
	bitmap_size = total_blocks / BLOCKS_PER_BUCKET;

	if (bitmap_size * BLOCKS_PER_BUCKET < total_blocks) {
		bitmap_size++;
	}
	// clear bitmap
	memset(bitmap, 0, bitmap_size);

	mem_start = (uint8_t *)BLOCK_ALIGN(((uint32_t)(bitmap + bitmap_size)));

#if 0
	qemu_write_string("error in memory need to be fixed");
#endif
}