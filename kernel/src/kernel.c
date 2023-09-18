#include <kernel.h>
#include <tty.h>
#include "../libc/stdio.h"
#include <gdt.h>
#include <ll_io.h>

void kernel_main(void)
{
	terminal_init();
	init_gdt();
}