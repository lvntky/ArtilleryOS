#include "../include/tty.h"

uint16_t *vid_mem = (uint16_t *)(VIDEO_MEM_ADDRESS);
uint16_t terminal_cursor_x = 0;
uint16_t terminal_cursor_y = 0;
uint16_t scroll_offset = 0;

// Define the number of rows and columns for the terminal.
#define TERMINAL_ROWS VGA_HEIGHT
#define TERMINAL_COLS VGA_WIDTH

uint16_t terminal_makechar(char c, enum VGA_COLOR color)
{
	return (color << 8) | c;
}

void scroll_terminal()
{
	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			vid_mem[y * VGA_WIDTH + x] =
				vid_mem[(y + 1) * VGA_WIDTH + x];
		}
	}

	for (int x = 0; x < VGA_WIDTH; x++) {
		vid_mem[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
			terminal_makechar(' ', VGA_COLOR_BLACK);
	}

	terminal_cursor_x = 0;
	terminal_cursor_y = VGA_HEIGHT - 1;
}

void terminal_putchar(int x, int y, char c, enum VGA_COLOR color)
{
	if (y >= VGA_HEIGHT) {
		scroll_terminal();
		y = VGA_HEIGHT - 1;
	}

	vid_mem[y * VGA_WIDTH + x] = terminal_makechar(c, color);
}

void terminal_write(char c, enum VGA_COLOR color)
{
	if (c == '\n') {
		terminal_cursor_x = 0;
		terminal_cursor_y++;

		if (terminal_cursor_y >= VGA_HEIGHT) {
			scroll_terminal();
			terminal_cursor_y = VGA_HEIGHT - 1;
		}
	} else {
		terminal_putchar(terminal_cursor_x, terminal_cursor_y, c,
				 color);
		terminal_cursor_x++;

		if (terminal_cursor_x >= VGA_WIDTH) {
			terminal_cursor_x = 0;
			terminal_cursor_y++;

			if (terminal_cursor_y >= VGA_HEIGHT) {
				scroll_terminal();
				terminal_cursor_y = VGA_HEIGHT - 1;
			}
		}
	}
}

void handle_backspace()
{
	if (terminal_cursor_x > 0) {
		terminal_cursor_x--;
	} else if (terminal_cursor_y > 0) {
		terminal_cursor_x = VGA_WIDTH - 1;
		terminal_cursor_y--;
	}

	vid_mem[terminal_cursor_y * VGA_WIDTH + terminal_cursor_x] =
		terminal_makechar(' ', VGA_COLOR_BLACK);
}

void terminal_write_default(char c)
{
	if (c == '\b') {
		handle_backspace();
	} else {
		terminal_write(c, VGA_COLOR_WHITE);
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

void print_logo()
{
	terminal_print_color(
		"  ___       _   _ _ _                   _____ _____ \n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		" / _ \\     | | (_) | |                 |  _  /  ___|\n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"/ /_\\ \\_ __| |_ _| | | ___ _ __ _   _  | | | \\ `--. \n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"|  _  | '__| __| | | |/ _ \\ '__| | | | | | | `--. \\\n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"| | | | |  | |_| | | |  __/ |  | |_| | \\ \\_/ /\\__/ /\n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"\\_| |_/_|   \\__|_|_|_|\\___|_|   \\__, |  \\___/\\____/ \n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"                                 __/ |              \n",
		VGA_COLOR_GREEN);
	terminal_print_color(
		"                                |___/               \n",
		VGA_COLOR_GREEN);
}

void terminal_init(void)
{
	terminal_cursor_x = 0;
	terminal_cursor_y = 0;
	for (int y = 0; y < TERMINAL_ROWS; y++) {
		for (int x = 0; x < TERMINAL_COLS; x++) {
			terminal_putchar(x, y, ' ', VGA_COLOR_BLACK);
		}
	}
	print_logo();
	terminal_print_color("v0.2.3", VGA_COLOR_YELLOW);
	printf("\n\n[INIT] terminal interface initialized successfully!\n");
}

void set_terminal_background(int x, int y, enum VGA_COLOR background_color)
{
	if (y < VGA_HEIGHT && x < VGA_WIDTH) {
		// Set the background color for the entire character
		vid_mem[y * VGA_WIDTH + x] =
			(background_color << 12) |
			(vid_mem[y * VGA_WIDTH + x] & 0xFF);
	}
}

void clear_terminal(enum VGA_COLOR background_color)
{
	terminal_cursor_x = 0;
	terminal_cursor_y = 0;
	for (int y = 0; y < TERMINAL_ROWS; y++) {
		for (int x = 0; x < TERMINAL_COLS; x++) {
			// Set the background color for each position
			terminal_putchar(x, y, ' ', background_color);
			set_terminal_background(x, y, background_color);
		}
	}
}

// LOGGER FUNCTIONS
uint16_t terminal_makechar_bg(char c, enum VGA_COLOR fg_color,
			      enum VGA_COLOR bg_color)
{
	return (bg_color << 12) | (fg_color << 8) | c;
}

void terminal_putchar_with_colors(int x, int y, char c, enum VGA_COLOR fg_color,
				  enum VGA_COLOR bg_color)
{
	if (y >= VGA_HEIGHT) {
		scroll_terminal();
		y = VGA_HEIGHT - 1;
	}

	vid_mem[y * VGA_WIDTH + x] =
		terminal_makechar_bg(c, fg_color, bg_color);
}

void terminal_putstr_with_colors(const char *str, enum VGA_COLOR fg_color,
				 enum VGA_COLOR bg_color)
{
	int i = 0;
	while (str[i] != '\0') {
		terminal_putchar_with_colors(terminal_cursor_x,
					     terminal_cursor_y, str[i],
					     fg_color, bg_color);
		terminal_cursor_x++;

		if (terminal_cursor_x >= VGA_WIDTH) {
			terminal_cursor_x = 0;
			terminal_cursor_y++;

			if (terminal_cursor_y >= VGA_HEIGHT) {
				scroll_terminal();
				terminal_cursor_y = VGA_HEIGHT - 1;
			}
		}

		i++;
	}
}
