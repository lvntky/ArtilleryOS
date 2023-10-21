#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	qemu_init_debug();
	gdt_init();
	idt_init();
	timer_init(50);
	keyboard_init();

	//paging_init();

	//pmm_test();
	// set_mode(320, 200, 8);
	// clear_screen_withcolor(0x04);
}
