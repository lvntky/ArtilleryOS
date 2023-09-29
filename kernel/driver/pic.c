#include "./include/pic.h"

void pic_init(void)
{
	outb(PIC_MASTER_CMD_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);
	outb(PIC_SLAVE_CMD_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);

	outb(PIC_MASTER_DATA_PORT, IRQ_BASE);
	outb(PIC_SLAVE_DATA_PORT, IRQ_BASE + 8);

	outb(PIC_MASTER_DATA_PORT, 4);
	outb(PIC_SLAVE_DATA_PORT, 2);

	outb(PIC_MASTER_DATA_PORT, PIC_ICW4_PC);
	outb(PIC_SLAVE_DATA_PORT, PIC_ICW4_PC);

	outb(PIC_MASTER_DATA_PORT, 0x00);
	outb(PIC_SLAVE_DATA_PORT, 0x00);
}

void pic_disable_irq(uint8_t irq)
{
	if (irq < 8) {
		// IRQ fuer den Master-PIC
		outb(PIC_MASTER_DATA_PORT,
		     insb(PIC_MASTER_DATA_PORT) | (1 << irq));
	} else if (irq < 16) {
		// IRQ fuer den Slave-PIC
		outb(PIC_SLAVE_DATA_PORT,
		     insb(PIC_SLAVE_DATA_PORT) | (1 << (irq - 8)));
	} else {
		printf("Unsupported IRQ %d\n", irq);
	}
}

// End of interrupt
void pic_eoi(uint8_t irq)
{
	if (irq > 16) {
		printf("Unsupproted IRQ %d\n", irq);
	}

	if (irq >= 8) {
		outb(PIC_SLAVE_CMD_PORT, PIC_EOI);
	}

	outb(PIC_MASTER_CMD_PORT, PIC_EOI);
}
