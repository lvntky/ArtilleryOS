#include "../include/kernel.h"
#include "../include/tty.h"
#include "../include/ll_io.h"

void kernel_main()
{
	terminal_init();

	terminal_print_color("\n=== ARTILLERY OS HARDCODED TESTS ===\n",
			     VGA_COLOR_GREEN);
	outb(0x60, 0xff);
}
