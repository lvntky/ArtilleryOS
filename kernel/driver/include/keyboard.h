#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../../include/io_port.h"
#include "../../libc/include/stdio.h"
#include "../../descriptor_tables/include/interrupt.h"
#include "../../descriptor_tables/include/isr.h"
#include "../../include/common.h"

void keyboard_init();

#endif