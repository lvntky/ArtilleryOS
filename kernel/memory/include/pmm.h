#ifndef _PMM_H
#define _PMM_H

#include "../../include/qemu_debug.h"
#include "../../libc/include/string.h"
#include <stdint.h>

#define BLOCK_SIZE 4096
#define BLOCKS_PER_BUCKET 8

#define SETBIT(i)                                                       \
	bitmap[i / BLOCKS_PER_BUCKET] = bitmap[i / BLOCKS_PER_BUCKET] | \
					(1 << (i % BLOCKS_PER_BUCKET))
#define CLEARBIT(i)                                                     \
	bitmap[i / BLOCKS_PER_BUCKET] = bitmap[i / BLOCKS_PER_BUCKET] & \
					(~(1 << (i % BLOCKS_PER_BUCKET)))
#define ISSET(i) \
	((bitmap[i / BLOCKS_PER_BUCKET] >> (i % BLOCKS_PER_BUCKET)) & 0x1)
#define GET_BUCKET32(i) (*((uint32_t *)&bitmap[i / 32]))

#define BLOCK_ALIGN(addr) (((addr)&0xFFFFF000) + 0x1000)

// Getting from linker.ld
extern uint32_t end;

void pmm_init(uint32_t);
uint32_t pmm_allocate_block();
void pmm_free_block(uint32_t);
uint32_t pmm_first_free_block();
void pmm_test();

#endif