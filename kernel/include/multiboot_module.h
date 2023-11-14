#ifndef _MULTIBOOT_MODULE_H_
#define _MULTIBOOT_MODULE_H_

#define ARE_MODULES_ENABLED(flags) flags & 0x00000008
#define MODULES_BASE_VIRTUAL_ADDRESS 0xC0400000
#define MODULES_BASE_PHYSICAL_ADDRESS 0x00400000

#include <stdint.h>
#include "multiboot.h"
#include "multiboot_util.h"
#include "../libc/include/string.h"

void move_multiboot_modules(multiboot_info_t *);

#endif