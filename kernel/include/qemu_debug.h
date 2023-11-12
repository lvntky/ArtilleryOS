#ifndef _QEMU_DEBUG_H
#define _QEMU_DEBUG_H

#include "io_port.h"
#include "../libc/include/stdio.h"
#include "registert.h"
#include <stdarg.h>

#define QEMU_LOG_SERIAL_PORT 0x3f8
#define QEMU_DEBUGCON_PORT 0xe9
#define POSITIVE_OUTPUT "\033[0;32m[ OK ]\033[0;37m    "
#define NEGATIVE_OUTPUT "\033[0;31m[ FAIL ]\033[0;37m  "
#define INFORMATION_OUTPUT "\033[0;33m[ INFO ]\033[0;37m  "
#define DEBUG_OUTPUT "\033[0;34m[ DEBUG ]\033[0;37m"
#define REGISTER_OUTPUT "[REGISTER]"
#define EXCEPTION_OUTPUT "[EXCEPTION]"
#define MEMORY_OUTPUT "[MEMORY DUMP]"
#define PAGE_OUTPUT "[PAGE DUMP]"

void qemu_init_debug();
void qemu_write_string(char *format, ...);
void qemu_write_char(char);
void qemu_print_register(register_t *);

#endif