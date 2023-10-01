#ifndef _KERNEL_H
#define _KERNEL_H

#include "../libc/stdio.h"
#include "tty.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"
#include "../descriptor_tables/gdt.h"
#include "../descriptor_tables/idt.h"
#include "../../gui/render_font.h"

void kernel_main();

#endif