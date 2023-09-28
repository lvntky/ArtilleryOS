#ifndef _KERNEL_H
#define _KERNEL_H

#include "../libc/stdio.h"
#include "tty.h"
#include "gdt.h"
//#include "../idt/idt.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"

void kernel_main();

#endif