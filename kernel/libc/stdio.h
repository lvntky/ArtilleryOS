#ifndef _STDIO_H
#define _STDIO_H

#include "../include/tty.h"
#include <stdarg.h>
#include <stdbool.h>

void itoa(int, char *, int);
int printf(const char *, ...);
void putchar(char c);

#endif