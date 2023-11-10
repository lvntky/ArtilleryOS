#ifndef _QEMU_DEBUG_H
#define _QEMU_DEBUG_H

#include "io_port.h"
#include "../libc/include/stdio.h"
#include "registert.h"
#include <stdarg.h>

#define QEMU_LOG_SERIAL_PORT 0x3f8
#define QEMU_DEBUGCON_PORT 0xe9
#define POSITIVE_OUTPUT "[+]"
#define NEGATIVE_OUTPUT "[-]"
#define INFORMATION_OUTPUT "[*]"
#define DEBUG_OUTPUT "->"
#define REGISTER_OUTPUT "[REGISTER]"
#define EXCEPTION_OUTPUT "[EXCEPTION]"
#define MEMORY_OUTPUT "[MEMORY]"

void qemu_init_debug();
void qemu_write_string(char *format, ...);
void qemu_write_char(char);
void qemu_print_register(register_t *);

#endif