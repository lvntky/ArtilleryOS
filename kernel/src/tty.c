#include "./tty.h"
#include "./config.h"

uint16_t *vid_mem = 0;
uint16_t terminal_column = 0; // x
uint16_t terminal_row = 0; // y

uint16_t terminal_makechar(char c, enum VGA_COLOR color)
{
	return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, enum VGA_COLOR color)
{
	vid_mem[(y * VGA_WIDTH) + x] = terminal_makechar(c, color);
}

void terminal_write(char c, enum VGA_COLOR color)
{
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		return;
	}

	terminal_putchar(terminal_column, terminal_row, c, color);
	terminal_column++;
	if (terminal_column >= VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}
}

size_t strlen(char *str)
{
	size_t len = 0;
	while (str[len]) {
		len++;
	}
	return len;
}

void terminal_print_color(char *str, enum VGA_COLOR color)
{
	for (size_t i = 0; i < strlen(str); i++) {
		terminal_write(str[i], color);
	}
}

void terminal_print(char *str)
{
	terminal_print_color(str, VGA_COLOR_WHITE);
}

void terminal_init(void)
{
	vid_mem = (uint16_t *)(VIDEO_MEM_ADDRESS);
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			terminal_putchar(x, y, ' ', 0);
		}
	}
	terminal_print_color(TERMINAL_WELCOM_MESSAGE, VGA_COLOR_WHITE);
	terminal_print_color(ARTILLERY_OS_VERSION, VGA_COLOR_RED);
}