#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"
#include "../libc/include/stdio.h"
#include "../descriptor_tables/include/isr.h"
#include "qemu_debug.h"
#include <stdint.h>

void timer_init(uint32_t);

#endif