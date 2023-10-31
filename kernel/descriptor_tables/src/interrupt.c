/**
 * @file exception.c
 * @author levent 
 * @brief hard interrupts
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/isr.h"
#include "../../include/common.h"
#include "../../include/qemu_debug.h"
#include "../../driver/include/pic.h"

isr_t interrupt_handlers[256];

/*
 * Register a function as the handler for a certian interrupt number, both exception and irq interrupt can change their handler using this function
 * */
void register_interrupt_handler(int num, isr_t handler)
{
	qemu_write_string("IRQ %d Registered\n", num);
	if (num < 256)
		interrupt_handlers[num] = handler;
}

void final_irq_handler(register_t *reg)
{
	if (interrupt_handlers[reg->int_no] != NULL) {
		isr_t handler = interrupt_handlers[reg->int_no];
		handler(reg);
	}
	irq_ack(reg->int_no);
}
