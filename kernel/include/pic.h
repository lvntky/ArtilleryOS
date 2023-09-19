/**
 * @file pic.h
 * @author levent kaya (leventkayadev@gmail.com)
 * @brief tiny header for programing the PIC
 * @version 0.1
 * @date 2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// check this referance -> https://wiki.osdev.org/8259_PIC
// I need to read it too :)

#ifndef _PIC_H
#define _PIC_H

#include "ll_io.h"
#include "interrupt.h"
#include "../libc/stdio.h"
#include <stdint.h>

#define PIC_MASTER 0x20 /* IO base address for master PIC */
#define PIC_SLAVE 0xA0 /* IO base address for slave PIC */
#define PIC_MASTER_COMMAND_PORT PIC_MASTER
#define PIC_MASTER_DATA_PORT (PIC_MASTER + 1)
#define PIC_SLAVE_COMMAND_PORT PIC_SLAVE
#define PIC_SLAVE_DATA_PORT (PIC_SLAVE + 1)

#define PIC_END_OF_INTERRUPT 0x20

#define PIC_ICW1_ICW4 0x01
#define PIC_ICW1_INIT 0x10
#define PIC_ICW4_PC 0x01

void pic_init(void);
void pic_disable_irq(uint8_t);
void pic_enable_irq(uint8_t);

/*inform the pic that irq has done and we are end of the interrupt*/
void pic_eoi(uint8_t);

#endif