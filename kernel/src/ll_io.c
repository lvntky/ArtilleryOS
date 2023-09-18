#include "../include/ll_io.h"

unsigned char insb(unsigned short port)
{
	unsigned char data;
	__asm__ __volatile__("inb %w1, %b0" : "=a"(data) : "Nd"(port));
	return data;
}
unsigned short insw(unsigned short port)
{
	unsigned short data;
	__asm__ __volatile__("inw %w1, %w0" : "=a"(data) : "Nd"(port));
	return data;
}

void outb(unsigned short port, unsigned char data)
{
	__asm__ __volatile__("outb %b0, %w1" : : "a"(data), "Nd"(port));
}
void outw(unsigned short port, unsigned short data)
{
	__asm__ __volatile__("outw %w0, %w1" : : "a"(data), "Nd"(port));
}