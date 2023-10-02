#include "../include/timer.h"

uint32_t tick = 0;
static void timer_callback(register_t *regs)
{
	tick++;
	printf("Tick: %d\n", tick);
}

void timer_init(uint32_t hertz)
{
	irq_install_handler(0, timer_callback);

	uint32_t divisor = 1193180 / hertz;

	// Send the command byte.
	outb(0x43, 0x32);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

	// Send the frequency divisor.
	outb(0x40, l);
	outb(0x40, h);

	__asm__ __volatile__("sti;");
}