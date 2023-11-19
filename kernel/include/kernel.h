#ifndef _KERNEL_H
#define _KERNEL_H

#include "multiboot_util.h"
#include "multiboot_module.h"
#include "system.h"
#include "common.h"
#include "../libc/include/stdio.h"
#include "../libc/include/math.h"
#include "tty.h"
#include "qemu_debug.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"
#include "../descriptor_tables/include/gdt.h"
#include "../descriptor_tables/include/idt.h"
#include "../descriptor_tables/include/tss.h"
#include "../include/timer.h"
#include "../driver/include/keyboard.h"
#include "../driver/include/cmos.h"
#include "../../gui/render_font.h"
#include "panic.h"
#include "../memory/include/paging.h"
#include "../memory/include/kernel_mem_limits.h"
#include "../memory/include/kernel_heap.h"
#include "../../gui/render_image.h"
#include "../../gui/bresenham.h"
#include "options.h"
#include "tty_cursor.h"
#include "../../util/include/art_linked_list.h"

void kernel_main(uint32_t, uint32_t, kernel_mem_limits_t, uint32_t);

#endif