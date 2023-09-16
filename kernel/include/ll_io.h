/**
 * @file ll_io.h
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief low level io functions with inline asm
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LL_IO_H__
#define __LL_IO_H__

/**
 * @brief read/write byte/word to/from port
 * 
 */
unsigned char inb(unsigned short);
void outb(unsigned short, unsigned char);
unsigned char inw(unsigned short);
void outw(unsigned short, unsigned short);

#endif