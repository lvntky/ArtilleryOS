#ifndef _TTY_H
#define _TTY_H

#include "vga_color_enum.h"
#include "../libc/include/stdio.h"
#include "qemu_debug.h"
#include "config.h"
#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEM_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void terminal_init(void);
uint16_t terminal_makechar(char c, enum VGA_COLOR color);
void terminal_putchar(int x, int y, char c, enum VGA_COLOR color);
void terminal_write(char c, enum VGA_COLOR color);
void terminal_write_default(char c);
void terminal_print_color(char *str, enum VGA_COLOR color);
void terminal_print(char *);
size_t strlen(char *str);
void terminal_print_color_logger(char *, enum VGA_COLOR, enum VGA_COLOR);
void clear_terminal(enum VGA_COLOR);
void terminal_putstr_with_colors(const char *, enum VGA_COLOR, enum VGA_COLOR);
#endif