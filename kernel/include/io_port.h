#ifndef _IO_PORT_H
#define _IO_PORT_H

// read 8 bit
unsigned char insb(unsigned short);
// read 16 bit
unsigned short insw(unsigned short);

// write 8 bit
void outb(unsigned short, unsigned char);
// write 16 bit
void outw(unsigned short, unsigned short);

#endif