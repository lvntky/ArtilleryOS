#include "../include/isr.h"
#include "../../include/io_port.h"

void *interrupt_handlers[256];

void install_interrupt_handler(int irq_no, void (*handler)(register_t *r))
{
	qemu_write_string("%s IRQ_NO: %d registered\n", POSITIVE_OUTPUT,
			  irq_no);
	interrupt_handlers[irq_no] = handler;
}

void interrupt_handler(register_t *r)
{
	/* This is a blank function pointer */
	void (*handler)(struct register_t * r);

	handler = interrupt_handlers[r->int_no - 32];
	if (handler) {
		handler(r);
	}

	if (r->int_no >= 40) {
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}
