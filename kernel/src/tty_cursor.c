#include "../include/tty_cursor.h"

void enable_cursor(uint8_t start, uint8_t end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (insb(0x3D5) & 0xC0) | start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (insb(0x3D5) & 0xE0) | end);
}
void disable_cursor();
void update_cursor(uint16_t x, uint16_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
uint16_t get_cursor_position();