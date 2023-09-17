#ifndef __LL_IO_H__
#define __LL_IO_H__

unsigned char insb(unsigned short port);
unsigned short insw(unsigned short port);

void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);

#endif
