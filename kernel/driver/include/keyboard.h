#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../../include/io_port.h"
#include "../../libc/include/stdio.h"
#include "../../descriptor_tables/include/isr.h"
#include "../../include/registert.h"
#include "../../include/qemu_debug.h"
#include "../../../gui/render_font.h"
#include "../../include/options.h"

void keyboard_init();

#endif