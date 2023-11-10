#ifndef _KERNEL_H
#define _KERNEL_H

#include "multiboot_util.h"
#include "system.h"
#include "../libc/include/stdio.h"
#include "tty.h"
#include "qemu_debug.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"
#include "../descriptor_tables/include/gdt.h"
#include "../descriptor_tables/include/idt.h"
#include "../descriptor_tables/include/tss.h"
#include "../include/timer.h"
#include "../driver/include/keyboard.h"
#include "../../gui/render_font.h"
#include "panic.h"
#include "../memory/include/paging.h"
#include "../../gui/render_image.h"
#include "options.h"

void kernel_main(multiboot_info_t *, uint32_t, uint32_t);

#endif