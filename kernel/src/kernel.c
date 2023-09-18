#include <kernel.h>
#include <tty.h>
#include "../libc/stdio.h"
#include <gdt.h>
#include <ll_io.h>

void kernel_main(void)
{
	terminal_init();
	printf("\nprintf actually works %s\n", ":^)");
	init_gdt();
	outb(0x60, 0xff);
}