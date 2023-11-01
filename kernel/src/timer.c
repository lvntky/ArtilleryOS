#include "../include/timer.h"

uint32_t tick = 0;
void timer_handler(register_t *reg)
{
	tick++;
}

void timer_init(uint32_t hertz)
{
	int divisor = 1193180 / hertz; /* Calculate our divisor */
	outb(0x43, 0x36); /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF); /* Set low byte of divisor */
	outb(0x40, divisor >> 8); /* Set high byte of divisor */

	install_interrupt_handler(0, timer_handler);
	qemu_write_string("%s PIT driver initialized\n", POSITIVE_OUTPUT);
}