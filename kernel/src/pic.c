#include "../include/pic.h"

void pic_init(void)
{
	outb(PIC_MASTER_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);
	outb(PIC_SLAVE_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INIT);
}