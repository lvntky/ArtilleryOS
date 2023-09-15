/**
 * @file ll_io.c
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief high level wrapper for handling low level io opt.
 * @version 0.1
 * @date 2023-09-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ll_io.h"

unsigned char insb(unsigned short port)
{
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}

unsigned short insw(unsigned short port)
{
	unsigned short ret;
	asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}

void outb(unsigned short port, unsigned char value)
{
	asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}
void outw(unsigned short port, unsigned short value)
{
	asm volatile("outw %1, %0" : : "dN"(port), "a"(value));
}
