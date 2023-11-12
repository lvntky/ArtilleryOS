#ifndef _MULTIBOOT_UTIL_H
#define _MULTIBOOT_UTIL_H

#include <stdbool.h>
#include "multiboot.h"
#include "common.h"
#include "../libc/include/stdio.h"
#include "qemu_debug.h"
#include "panic.h"
#include "../memory/include/kernel_mem_limits.h"

void display_memory_info(multiboot_info_t *);
void check_mboot_bootloader_magic(uint32_t);
void display_kernel_mem_info(kernel_mem_limits_t *);
multiboot_info_t *remap_multiboot_info(uint32_t);

#endif