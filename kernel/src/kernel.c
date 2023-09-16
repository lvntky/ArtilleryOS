#include "../include/kernel.h"
#include "../include/tty.h"
#include "../include/ll_io.h"

void kernel_main()
{
	terminal_init();
	outb(0x60, 0xff);
}
