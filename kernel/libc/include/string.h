#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void strncpy(char *destination, char *source, size_t n);
void strcpy(char *, char *);
char* strcat(char *destination, char *source);
char* strncat(char *destination, char *source, size_t n);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(char *, char *str2);
char* strchr(const char* str, int ch);
char* strtok(char* str, const char* delim);

#endif
