#include "./tty.h"
#include "./vga_color.h"

uint16_t *vid_mem = (uint16_t *)(VIDEO_MEM_ADDRESS);

void terminal_init(void)
{
	size_t vga_area = VGA_WIDTH * VGA_HEIGHT;
	for (size_t i = 0; i < vga_area; i++) {
		vid_mem[i] = terminal_putchar('.', VGA_COLOR_BLACK);
	}
	terminal_write(TERMINAL_MESSAGE, VGA_COLOR_BRIGHT_WHITE);
	terminal_write("###", VGA_COLOR_YELLOW);
}

uint16_t terminal_putchar(char c, enum VGA_COLOR color)
{
	return (color << 8) | c;
}

void terminal_write(char *c, char color)
{
	for (size_t i = 0; i < strlen(c); i++) {
		vid_mem[i] = terminal_putchar(c[i], color);
	}
}

int strlen(char *str)
{
	int len = 0;
	while (str[len]) {
		len++;
	}
	return len;
}
