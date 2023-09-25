#ifndef _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include "../../include/io_port.h"
#include "../../libc/stdio.h"
#include "../../libc/string.h"
#include <stdint.h>
#include <stdbool.h>

#define VGA_MISC_PORT 0x3c2
#define VGA_CRTC_INDEX_PORT 0x3d4
#define VGA_CRTC_DATA_PORT 0x3d5
#define VGA_SEQUENCER_INDEX_PORT 0x3c4
#define VGA_SEQUENCER_DATA_PORT 0x3c5
#define VGA_GFX_CONTROLLER_INDEX_PORT 0x3ce
#define VGA_GFX_CONTROLLER_DATA_PORT 0x3cf
#define VGA_ATTRIBUTE_CONTROLLER_INDEX_PORT 0x3c0
#define VGA_ATTRIBUTE_CONTROLLER_READ_PORT 0x3c1
#define VGA_ATTRIBUTE_CONTROLLER_WRITE_PORT 0x3c0
#define VGA_ATTRIBUTE_CONTROLLER_RESET_PORT 0x3da

bool is_mode_supported(uint32_t, uint32_t, uint32_t);
bool set_mode(uint32_t, uint32_t, uint32_t);
void write_registers(uint8_t *);
uint8_t *get_frame_bufer_index();
void put_pixel(uint32_t, uint32_t, uint8_t);
uint8_t get_color_index(uint8_t, uint8_t, uint8_t);
void draw(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
#endif