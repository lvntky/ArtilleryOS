#include "isr.h"

void isr_handler(registers_t regs)
{
	printf("INTERRUPT: %d\n", regs.int_no);
}