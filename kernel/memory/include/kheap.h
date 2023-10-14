#ifndef _KHEAP_H
#define _KHEAP_H

#include <stdint.h>

// vanilla
uint32_t kmalloc(uint32_t);

// page aligned
uint32_t kmalloc_aligned(uint32_t);

// returns physical address
uint32_t kmalloc_physical(uint32_t, uint32_t *);

// both page aligned and returns physical address
uint32_t kmalloc_aligned_physical(uint32_t, uint32_t *);

#endif