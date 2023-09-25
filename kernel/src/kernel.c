#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	idt_init();
	outb(0x60, 0x10);
	vga_enter();
	vga_clear_screen();
}
