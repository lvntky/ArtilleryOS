#include "../include/pic.h"

void pic_init(void)
{
	outb(PIC_MASTER_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);
	outb(PIC_SLAVE_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);

	outb(PIC_MASTER_DATA_PORT, INT_IRQ_BASE);
	outb(PIC_SLAVE_DATA_PORT, INT_IRQ_BASE + 8);

	outb(PIC_MASTER_DATA_PORT, 4);
	outb(PIC_SLAVE_DATA_PORT, 2);

	outb(PIC_MASTER_DATA_PORT, PIC_ICW4_PC);
	outb(PIC_SLAVE_DATA_PORT, PIC_ICW4_PC);

	outb(PIC_MASTER_DATA_PORT, 0x00);
	outb(PIC_SLAVE_DATA_PORT, 0x00);
}

// TODO: Implement and use panic() instead of printf()
void pic_disable_irq(uint8_t irq)
{
	if (irq < 8) {
		outb(PIC_MASTER_DATA_PORT,
		     insb(PIC_MASTER_DATA_PORT) | (1 << irq));
	} else if (irq < 16) {
		outb(PIC_SLAVE_DATA_PORT,
		     insb(PIC_SLAVE_DATA_PORT) | (1 << (irq - 8)));
	} else {
		printf("Invalid IRQ: %d\n", irq);
	}
}

void pic_enable_irq(uint8_t irq)
{
	if (irq < 8) {
		outb(PIC_MASTER_DATA_PORT,
		     insb(PIC_MASTER_DATA_PORT) & (~(1 << irq)));
	} else if (irq < 16) {
		outb(PIC_SLAVE_DATA_PORT,
		     insb(PIC_SLAVE_DATA_PORT) & (~(1 << (irq - 8))));
	} else {
		printf("Invalid IRQ: %d\n", irq);
	}
}
void pic_eoi(uint8_t irq)
{
	if (irq > 16) {
		printf("Invalid IRQ: %d\n", irq);
	}
	if (irq >= 8) {
		outb(PIC_SLAVE_COMMAND_PORT, PIC_END_OF_INTERRUPT);
	}
	outb(PIC_MASTER_COMMAND_PORT, PIC_END_OF_INTERRUPT);
}