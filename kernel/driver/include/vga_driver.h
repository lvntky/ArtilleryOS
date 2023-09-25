#ifndef _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include "../../include/io_port.h"
#include "../../libc/stdio.h"
#include "../../libc/string.h"

#define GRAPHICS_REG_ADDR 0x3ce
#define GRAPHICS_REG_DATA 0x3cf
#define GRAPHICS_IDX_MISC 0x06

#define COLOR_BLACK 0x0
#define COLOR_GREEN 0x2
#define COLOR_PURPLE 0xf

#define VGA_ADDRESS 0xB8000

unsigned int get_graphics_reg(unsigned int);
void set_graphics_reg(unsigned int, unsigned int);
void vga_info();
void vga_enter();
void vga_clear_screen();
void vga_plot_pixel(int, int, unsigned short);

#endif