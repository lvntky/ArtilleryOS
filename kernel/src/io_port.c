#include "../include/io_port.h"


uint8_t insb(uint16_t port)
{
	unsigned char data;
	__asm__ __volatile__("inb %w1, %b0" : "=a"(data) : "Nd"(port));
	return data;
}
uint16_t insw(uint16_t port)
{
	unsigned short data;
	__asm__ __volatile__("inw %w1, %w0" : "=a"(data) : "Nd"(port));
	return data;
}

void outb(uint16_t port, uint8_t data)
{
	__asm__ __volatile__("outb %b0, %w1" : : "a"(data), "Nd"(port));
}
void outw(uint16_t port, uint16_t data)
{
	__asm__ __volatile__("outw %w0, %w1" : : "a"(data), "Nd"(port));
}
