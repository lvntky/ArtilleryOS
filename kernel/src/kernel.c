#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	idt_init();
	idt_activate();
	outb(0x60, 0x10);

	int i = 1000;
	while (i > 0) {
		printf("Setting graphics mode... %d\n", i);
		i--;
	}

	set_mode(320, 200, 8);
	clear_screen();
}
