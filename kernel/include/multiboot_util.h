#ifndef _MULTIBOOT_UTIL_H
#define _MULTIBOOT_UTIL_H

#include <stdbool.h>
#include "multiboot.h"
#include "../libc/include/stdio.h"
#include "qemu_debug.h"

void print_multiboot_magic(unsigned int);
bool is_multiboot_info_present(multiboot_info_t *);

#endif