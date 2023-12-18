#ifndef __IO_PORT_H__
#define __IO_PORT_H__

#include <stdint.h>

// read 8 bit
uint8_t insb(uint16_t);
// read 16 bit
uint16_t insw(uint16_t);

// write 8 bit
void outb(uint16_t, uint8_t);
// write 16 bit
void outw(uint16_t, uint16_t);

#endif
