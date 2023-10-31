#include "./include/pic.h"

void pic_init()
{
	// ICW1
	outb(PIC1_COMMAND, ICW1);
	outb(PIC2_COMMAND, ICW1);

	// ICW2, irq 0 to 7 is mapped to 0x20 to 0x27, irq 8 to F is mapped to 28 to 2F
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);

	// ICW3, connect master pic with slave pic
	outb(PIC1_DATA, 0x4);
	outb(PIC2_DATA, 0x2);

	// ICW4, set x86 mode
	outb(PIC1_DATA, 1);
	outb(PIC2_DATA, 1);

	// clear the mask register
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
}

/*
 * Tell PIC interrupt is handled
 * */
void irq_ack(uint8_t irq)
{
	if (irq >= 0x28)
		outb(PIC2, PIC_EOI);
	outb(PIC1, PIC_EOI);
}
