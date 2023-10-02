#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"
#include "../libc/stdio.h"
#include "../descriptor_tables/irq.h"
#include <stdint.h>

void timer_init(uint32_t);

#endif