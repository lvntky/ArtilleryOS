#ifndef _REDNER_FONT_H
#define _REDNER_FONT_H

#include "../kernel/driver/include/vga_driver.h"
#include <stdint.h>

void gui_draw_string(uint32_t, uint32_t, const char *, uint8_t);

#endif