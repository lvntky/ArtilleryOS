#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <stdint.h>
#include "../libc/stdio.h"

#define INT_IRQ_BASE 0x20

uint32_t handle_interrupt(uint8_t interrupt, uint32_t esp);

#endif
