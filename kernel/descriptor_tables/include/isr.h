#ifndef _ISR_H
#define _ISR_H

#include "idt.h"
#include "../../include/common.h"
#include "../../libc/include/stdio.h"

void isrs_install();
void isr_install_handler(int isr, void (*handler)(register_t *r));

#endif