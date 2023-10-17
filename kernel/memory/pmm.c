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

	printf("[INIT] PMM initialized successfully!\n");

#if 0
	qemu_write_string("error in memory need to be fixed");
#endif
}

uint32_t pmm_first_free_block()
{
	for (uint32_t i = 0; i < total_blocks; i++) {
		if (!ISSET(i)) {
			return i;
		}
	}
	qemu_write_string("Running out of memory!\n");
	return (uint32_t)-1;
}

uint32_t pmm_allocate_block()
{
	uint32_t free_block = pmm_first_free_block();
	SETBIT(free_block);
	return free_block;
}

void pmm_free_block(uint32_t block_no)
{
	CLEARBIT(block_no);
}

void pmm_test()
{
	printf("\nPMM TEST\n");
	uint32_t t1 = pmm_first_free_block();
	printf("first free block is %u\n", t1);

	void *ret = (void *)pmm_allocate_block();
	printf("first allocated block addr 0x%p\n", ret);

	uint32_t t2 = pmm_first_free_block();
	printf("second free block is %u\n", t2);

	ret = (void *)pmm_allocate_block();
	printf("second allocated block addr 0x%p\n", ret);

	pmm_free_block(t2);
	t2 = pmm_first_free_block();
	printf("third free block(after freeing the second) is %u\n", t2);

	pmm_free_block(t1);
	t1 = pmm_first_free_block();
	printf("third free block(after freeing the first) is %u\n", t1);
}