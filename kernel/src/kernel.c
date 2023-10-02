#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	gdt_init();
	idt_init();
	timer_init(50);
	keyboard_init();

	//set_mode(320, 200, 8);
	//clear_screen_withcolor(0x04);
}
