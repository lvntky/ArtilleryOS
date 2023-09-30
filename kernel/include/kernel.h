#ifndef _KERNEL_H
#define _KERNEL_H

#include "../libc/stdio.h"
#include "tty.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"
#include "../descriptor_tables/descriptor_tables.h"

void kernel_main();

#endif