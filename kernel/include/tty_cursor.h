#ifndef _TTY_CURSOR_H_
#define _TTY_CURSOR_H_

#include <stdint.h>
#include "io_port.h"
#include "tty.h"

void enable_cursor(uint8_t, uint8_t);
void disable_cursor();
void update_cursor(uint16_t, uint16_t);
uint16_t get_cursor_position();

#endif