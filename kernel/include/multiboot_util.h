#ifndef _MULTIBOOT_UTIL_H
#define _MULTIBOOT_UTIL_H

#include <stdbool.h>
#include "multiboot.h"
#include "../libc/include/stdio.h"
#include "qemu_debug.h"
#include "panic.h"

void display_memory_info(multiboot_info_t *, uint32_t);
void check_mboot_bootloader_magic(uint32_t);

#endif