#ifndef _IRQ_H
#define _IRQ_H

#include "../driver/include/pic.h"
#include "../include/common.h"
#include "../include/io_port.h"
#include "../libc/stdio.h"
#include "idt.h"

void irqs_install();

#endif