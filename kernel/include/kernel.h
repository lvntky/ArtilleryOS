#ifndef _KERNEL_H
#define _KERNEL_H

#define GUI_MODE 0

#include "multiboot_util.h"
#include "system.h"
#include "../libc/include/stdio.h"
#include "tty.h"
#include "qemu_debug.h"
#include "cpu_info.h"
#include "../driver/include/vga_driver.h"
#include "../descriptor_tables/include/gdt.h"
#include "../descriptor_tables/include/idt.h"
#include "../../gui/render_font.h"
#include "timer.h"
#include "../driver/include/keyboard.h"
#include "panic.h"
#include "../../gui/render_image.h"

void kernel_main(multiboot_info_t *, unsigned int);

#endif