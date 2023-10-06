#include "../include/panic.h"

void panic(char *message, char *location)
{
	// Disable interrupts
	asm volatile("cli");

	// Clear terminal with red background
	clear_terminal(VGA_COLOR_RED);
	printf("\n\n");

	// Display panic message
	terminal_putstr_with_colors(
		"================================= KERNEL PANIC =================================",
		VGA_COLOR_WHITE, VGA_COLOR_RED);

	printf("\n");
	terminal_putstr_with_colors(
		"The kernel encountered an error from which it could not recover.",
		VGA_COLOR_WHITE, VGA_COLOR_RED);
	printf("\n");
	terminal_putstr_with_colors(
		"This could be due to hardware issues,or kernel bug.",
		VGA_COLOR_WHITE, VGA_COLOR_RED);

	printf("\n\n\n\nLocation: %s\n", location);
	printf("Message: %s", message);
	// Halt the system
	asm volatile("hlt");
}