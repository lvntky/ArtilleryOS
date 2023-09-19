#include <kernel.h>
#include <tty.h>
#include "../libc/stdio.h"
#include <gdt.h>
#include <ll_io.h>
#include "../include/interrupt.h"

int test_zero()
{
	int a = 5;
	int b = 0;

	return a / b;
}
void kernel_main(void)
{
	terminal_init();
	init_gdt();
	init_interrupt_manager(0x20);
	interrupt_activate();
	int result = 5 / 0;
}