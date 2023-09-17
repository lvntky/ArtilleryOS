#include "../include/tty.h"
#include "../include/config.h"

uint16_t *vid_mem = (uint16_t *)(VIDEO_MEM_ADDRESS);
uint16_t terminal_column = 0; // x
uint16_t terminal_row = 0; // y

// Define the number of rows and columns for the terminal.
#define TERMINAL_ROWS VGA_HEIGHT
#define TERMINAL_COLS VGA_WIDTH

// Track the current scroll position.
uint16_t scroll_offset = 0;

uint16_t terminal_makechar(char c, enum VGA_COLOR color)
{
	return (color << 8) | c;
}

void scroll_terminal()
{
	// Shift the entire screen content up by one row.
	for (int y = 0; y < TERMINAL_ROWS - 1; y++) {
		for (int x = 0; x < TERMINAL_COLS; x++) {
			vid_mem[y * TERMINAL_COLS + x] =
				vid_mem[(y + 1) * TERMINAL_COLS + x];
		}
	}

	// Clear the last row.
	for (int x = 0; x < TERMINAL_COLS; x++) {
		vid_mem[(TERMINAL_ROWS - 1) * TERMINAL_COLS + x] =
			terminal_makechar(' ', VGA_COLOR_BLACK);
	}
}

void terminal_putchar(int x, int y, char c, enum VGA_COLOR color)
{
	// Check for overflow and scroll if needed.
	if (y >= TERMINAL_ROWS) {
		scroll_terminal();
		y = TERMINAL_ROWS - 1;
	}

	vid_mem[(y * TERMINAL_COLS) + x] = terminal_makechar(c, color);
}

void terminal_write(char c, enum VGA_COLOR color)
{
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;

		// Check if we've reached the end of the screen and scroll if needed.
		if (terminal_row >= TERMINAL_ROWS) {
			scroll_terminal();
			terminal_row = TERMINAL_ROWS - 1;
		}
	} else {
		terminal_putchar(terminal_column, terminal_row, c, color);
		terminal_column++;

		// Check if we've reached the end of the line and wrap to the next line.
		if (terminal_column >= TERMINAL_COLS) {
			terminal_column = 0;
			terminal_row++;
		}

		// Check if we've reached the end of the screen and scroll if needed.
		if (terminal_row >= TERMINAL_ROWS) {
			scroll_terminal();
			terminal_row = TERMINAL_ROWS - 1;
		}
	}
}

void terminal_write_default(char c)
{
	terminal_write(c, VGA_COLOR_WHITE);
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
	for (int y = 0; y < TERMINAL_ROWS; y++) {
		for (int x = 0; x < TERMINAL_COLS; x++) {
			terminal_putchar(x, y, ' ', VGA_COLOR_BLACK);
		}
	}
	terminal_print_color("=== ARTILLERY OS ===\n", VGA_COLOR_GREEN);
	terminal_print_color("v0.0.1-alpha", VGA_COLOR_RED);
}