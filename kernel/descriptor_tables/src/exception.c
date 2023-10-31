/**
 * @file exception.c
 * @author levent 
 * @brief soft exceptions
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/isr.h"
#include "../../include/common.h"
#include "../../include/qemu_debug.h"

char *exception_messages[32] = { "Division By Zero",
				 "Debug",
				 "Non Maskable Interrupt",
				 "Breakpoint",
				 "Into Detected Overflow",
				 "Out of Bounds",
				 "Invalid Opcode",
				 "No Coprocessor",
				 "Double Fault",
				 "Coprocessor Segment Overrun",
				 "Bad TSS",
				 "Segment Not Present",
				 "Stack Fault",
				 "General Protection Fault",
				 "Page Fault",
				 "Unknown Interrupt",
				 "Coprocessor Fault",
				 "Alignment Check",
				 "Machine Check",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved",
				 "Reserved" };

void final_exception_handler(register_t reg)
{
	if (reg.int_no < 32) {
		qemu_write_string("EXCEPTION: %s (err code is %x)\n",
				  exception_messages[reg.int_no], reg.err_code);
		qemu_print_register(&reg);
		for (;;)
			;
	}
	if (interrupt_handlers[reg.int_no] != NULL) {
		isr_t handler = interrupt_handlers[reg.int_no];
		handler(&reg);
	}
}
