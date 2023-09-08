#ifndef __TTY_H__
#define __TTY_H__

#include "vga_color.h"
#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEM_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 20
#define TERMINAL_MESSAGE "Artillery OS v0.1.0 ~ WELCOME !"

void terminal_init(void);
uint16_t terminal_putchar(char c, enum VGA_COLOR color);
void terminal_write(char *c, char color);
int strlen(char *str);

#endif