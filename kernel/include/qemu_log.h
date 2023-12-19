#ifndef __QEMU_LOG_H__
#define __QEMU_LOG_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void qemu_log_putc(char);
int init_serial_port(uint16_t );

#endif // __QEMU_LOG_H__
