/**
 * @file ll_io.h
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief  Low level IO functions
 * @version 0.1
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __LL_IO_H__
#define __LL_IO_H__

unsigned char insb(unsigned short);
unsigned short insw(unsigned short);

void outb(unsigned short, unsigned char);
void outw(unsigned short, unsigned short);

#endif