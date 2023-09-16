#include "../include/ll_io.h"

unsigned char inb(unsigned short port)
{
	unsigned char value;
	__asm__ __volatile__("inb %1, %0" : "=a"(value) : "dN"(port));
	return value;
}

unsigned char inw(unsigned short port)
{
	unsigned short value;
	__asm__ __volatile__("inw %1, %0" : "=a"(value) : "dN"(port));
	return value;
}

void outb(unsigned short port, unsigned char data)
{
	__asm__ __volatile__("outb %0, %1" ::"a"(data), "dN"(port));
}

void outw(unsigned short port, unsigned short data)
{
	__asm__ __volatile__("outw %0, %1" ::"a"(data), "dN"(port));
}