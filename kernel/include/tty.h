#ifndef __TTY_H__
#define __TTY_H__

#include "vga_color.h"
#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEM_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TERMINAL_WELCOM_MESSAGE "\nArtillery OS  ~~ WELCOME ! ~~\n"

void terminal_init(void);
uint16_t terminal_makechar(char c, enum VGA_COLOR color);
void terminal_putchar(int x, int y, char c, enum VGA_COLOR color);
void terminal_write(char c, enum VGA_COLOR color);
void terminal_print_color(char *str, enum VGA_COLOR color);
void terminal_print(char *);
size_t strlen(char *str);
void terminal_print_hex_digit(uint8_t, enum VGA_COLOR color);
void terminal_print_hex(uint8_t);

#endif