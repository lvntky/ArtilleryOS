#include "../include/isr.h"

char *exception_messages[] = { "Division By Zero",
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

void exception_fault_handler(register_t *r)
{
	if (r->int_no < 32) {
		qemu_write_string("%s %s - ERR_NO: %d\n", EXCEPTION_OUTPUT,
				  exception_messages[r->int_no], r->int_no);
		qemu_print_register(r);
		panic(exception_messages[r->int_no], "exception.c");
		for (;;)
			;
	}
}
