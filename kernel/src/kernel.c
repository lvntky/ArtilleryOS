#include "../include/kernel.h"
#include "../include/tty.h"
#include "../include/idt.h"
#include "../libc/stdio.h"
#include "../include/ll_io.h"

void kernel_main()
{
	terminal_init();
	idt_init();

	printf("\nHi, we have a printf function now on date %d - %d - %d", 17,
	       9, 2023);
	printf("\nWe can even handle the hex values -> %x", 0xFF);
	printf("\nAnd string too -> %s", ":^)");

	outb(0x60, 0xff);
}
