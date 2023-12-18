/**
   Qemu E9 HACK
 */
#ifndef __E9_HACK_H__
#define __E9_HACK_H__

#include <stdarg.h>
#include <stddef.h>

void e9_log_putc(char );
void e9_log_print(const char *);
void e9_log_puts(const char *);
void e9_log_printf(const char *, ...);

#endif // __E9_HACK_H__
