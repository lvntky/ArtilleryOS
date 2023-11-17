#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);

int strcmp(char *, char *str2);

#endif