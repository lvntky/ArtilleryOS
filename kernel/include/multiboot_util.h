#ifndef _MULTIBOOT_UTIL_H
#define _MULTIBOOT_UTIL_H

#include <stdbool.h>
#include "multiboot.h"
#include "../libc/include/stdio.h"
#include "qemu_debug.h"

void display_memory_info(multiboot_info_t *);

#endif