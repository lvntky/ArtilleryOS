/**
 * @file bresenham.h
 * @author levent
 * @brief couple of low level graphics experiments
 * @version 0.1
 * @date 2023-11-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _BRESENHAM_H_
#define _BRESENHAM_H_

#include "../kernel/driver/include/vga_driver.h"
#include <stdint.h>
#include <stddef.h>
#include "../kernel/libc/include/stdlib.h"

typedef struct brs_point {
	uint32_t brs_x;
	uint32_t brs_y;

} __attribute__((packed)) brs_point_t;

void brs_drawline(brs_point_t *, brs_point_t *, uint8_t);

#endif