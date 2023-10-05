#ifndef _IRQ_H
#define _IRQ_H

#include "../../driver/include/pic.h"
#include "../../include/common.h"
#include "../../include/io_port.h"
#include "../../libc/include/stdio.h"
#include "idt.h"

void irqs_install();
void irq_install_handler(int irq, void (*handler)(register_t *r));

#endif