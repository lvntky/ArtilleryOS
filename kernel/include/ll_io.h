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

static inline unsigned char in_byte(unsigned short);
static inline unsigned short in_word(unsigned short);

static inline void out_byte(unsigned short, unsigned char);
static inline void out_word(unsigned short, unsigned short);

#endif