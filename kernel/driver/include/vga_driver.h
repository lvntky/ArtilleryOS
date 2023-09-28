#ifndef _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include "../../include/io_port.h"
#include "../../libc/stdio.h"
#include "../../libc/string.h"
#include <stdint.h>
#include <stdbool.h>

// VGA ports
#define MISC_PORT 0x3c2
#define CRT_CONTROLLER_INDEX_PORT 0x3d4
#define CRT_CONTROLLER_DATA_PORT 0x3d5
#define SEQUENCER_INDEX_PORT 0x3c4
#define SEQUENCER_DATA_PORT 0x3c5
#define GRAPHICS_CONTROLLER_INDEX_PORT 0x3ce
#define GRAPHICS_CONTROLLER_DATA_PORT 0x3cf
#define ATTRIBUTE_CONTROLLER_INDEX_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_READ_PORT 0x3c1
#define ATTRIBUTE_CONTROLLER_WRITE_PORT 0x3c0
#define ATTRIBUTE_CONTROLLER_RESET_PORT 0x3da

// VGA screen dimensions
#define VGA_GFX_WIDTH 320
#define VGA_GFX_HEIGHT 200
#define VGA_GFX_COLOR_DEPTH 8

bool is_mode_supported(uint32_t, uint32_t, uint32_t);
int set_mode(uint32_t, uint32_t, uint32_t);
void write_registers(uint8_t *);
uint8_t *get_frame_bufer_index();
void put_pixel(uint32_t, uint32_t, uint8_t);
uint8_t get_color_index(uint8_t, uint8_t, uint8_t);
void put_pixel_rgb(uint32_t, uint32_t, uint8_t, uint8_t, uint8_t);
void clear_screen();
void color_demo();
void clear_screen_withcolor(uint8_t);

#endif