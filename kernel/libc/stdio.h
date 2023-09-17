#ifndef __STDIO_H__
#define __STDIO_H__

#include "../include/tty.h"
#include <stdarg.h>
#include <stdbool.h>

void itoa(int, char *, int);
int printf(const char *, ...);

#endif