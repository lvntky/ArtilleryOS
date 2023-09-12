// TODO: Fix required!

#include "ll_io.h"

static inline unsigned char in_byte(unsigned short port)
{
	unsigned char value;
	__asm__ __volatile__("inb %1, %0" : "=a"(value) : "dN"(port));
	return value;
}

static inline unsigned short in_word(unsigned short port)
{
	unsigned short value;
	__asm__ __volatile__("inw %1, %0" : "=a"(value) : "dN"(port));
	return value;
}

static inline void out_byte(unsigned short port, unsigned char data)
{
	__asm__ __volatile__("outb %0, %1" ::"a"(data), "dN"(port));
}

static inline void out_word(unsigned short port, unsigned short data)
{
	__asm__ __volatile__("outw %0, %1" ::"a"(data), "dN"(port));
}