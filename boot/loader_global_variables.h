#ifndef _LOADER_EXTERNAL_VARIABLES_H_
#define _LOADER_EXTERNAL_VARIABLES_H_

#include <stdint.h>

uint32_t KERNEL_VIRTUAL_BASE;

void *kernel_stack_lowest_address;
void *page_directory_virtual_address;
void *page_directory_physical_address;

#endif