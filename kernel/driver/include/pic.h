#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>
#include "../../include/io_port.h"
#include "../../include/config.h"
#include "../../libc/stdio.h"

/**
 * NOTE: This microcontroller INTEL 8259A used hardware interrupts only. 
 * 
 */

/** IO BASE ADDRESS FOR INTEL 8259A*/
#define PIC_MASTER 0x20
#define PIC_SLAVE 0xA0
#define PIC_MASTER_CMD_PORT PIC_MASTER
#define PIC_MASTER_DATA_PORT PIC_MASTER + 1
#define PIC_SLAVE_CMD_PORT PIC_SLAVE
#define PIC_SLAVE_DATA_PORT PIC_SLAVE + 1

/** Initialization Control Word*/
#define PIC_ICW1_ICW4 0x01
#define PIC_ICW1_INIT 0x10
#define PIC_ICW4_PC 0x01
#define PIC_EOI 0x20

void pic_init();

#endif