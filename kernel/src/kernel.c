#include "../include/kernel.h"
#include "../include/tty.h"
#include "../include/idt.h"
#include "../libc/stdio.h"

extern void problem();

void kernel_main()
{
	terminal_init();
	idt_init();
	//problem();
	printf("\nHi, we have a printf function now on date %d - %d - %d", 17,
	       9, 2023);
	printf("\nWe can even handle the hex values -> %x", 0xFF);
	printf("\nAnd string too -> %s", ":^)");
}
