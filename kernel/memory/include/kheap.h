#ifndef _KHEAP_H
#define _KHEAP_H

#include <stdint.h>
#include <stdbool.h>

/* Vanilla */
uint32_t kmalloc_vanilla(uint32_t);

/* Allocate aligned memory */
uint32_t kmalloc_aligned(uint32_t);

/* Allocate memory, return physical address of it */
uint32_t kmalloc_return_physical_addr(uint32_t, uint32_t *);

/* Allocate aligned memory return physical address of it*/
uint32_t kmalloc_aligned_and_return_physical_addr(uint32_t, uint32_t *);

/*
 More internal version of vanilla. 
* You can set size
* align or not 
* and physical address
*/
uint32_t kmalloc(uint32_t, bool, uint32_t *);

#endif