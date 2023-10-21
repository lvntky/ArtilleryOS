#include "include/kheap.h"

// Comes from linker.ld
extern uint32_t end;
uint32_t placement_addr = (uint32_t)&end;

uint32_t kmalloc(uint32_t size, bool is_align, uint32_t *physical_addr)
{
	if (is_align == 1 && (placement_addr & 0xFFFFF000)) {
		placement_addr &= 0xFFFFF000;
		placement_addr += 0x1000;
	}
	if (physical_addr) {
		*physical_addr = placement_addr;
	}
	uint32_t tmp = placement_addr;
	placement_addr += size;

	return tmp;
}

uint32_t kmalloc_aligned(uint32_t size)
{
	return kmalloc(size, true, 0);
}

uint32_t kmalloc_return_physical_addr(uint32_t size, uint32_t *phsyical_addr)
{
	return kmalloc(size, false, phsyical_addr);
}

uint32_t kmalloc_aligned_and_return_physical_addr(uint32_t size,
						  uint32_t *phsyical_addr)
{
	return kmalloc(size, true, phsyical_addr);
}

uint32_t kmalloc_vanilla(uint32_t size)
{
	return kmalloc(size, false, 0);
}