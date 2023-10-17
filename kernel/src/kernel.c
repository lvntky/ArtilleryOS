#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	qemu_init_debug();
	gdt_init();
	idt_init();
	timer_init(50);
	keyboard_init();
	get_cpu_info();

	pmm_init(1096 * MB);
	// set_mode(320, 200, 8);
	// clear_screen_withcolor(0x04);
}
