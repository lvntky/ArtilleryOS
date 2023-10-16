#ifndef _QEMU_DEBUG_H
#define _QEMU_DEBUG_H

#include "io_port.h"
#include "../libc/include/stdio.h"

#define QEMU_LOG_SERIAL_PORT 0x3f8
#define QEMU_DEBUGCON_PORT 0xe9

void qemu_init_debug();
void qemu_write_string(char *message);
void qemu_write_char(char);

#endif