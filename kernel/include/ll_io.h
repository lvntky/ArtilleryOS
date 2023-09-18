/**
 * @file ll_io.h
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief low level io functions
 * @version 0.1
 * @date 2023-09-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _LL_IO_H
#define _LL_IO_H

// read 8 bit
unsigned char insb(unsigned short);
// read 16 bit
unsigned short insw(unsigned short);

// write 8 bit
void outb(unsigned short, unsigned char);
// write 16 bit
void outw(unsigned short, unsigned short);

#endif