#include "../include/kernel.h"

typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;

void call_constructors()
{
	for (constructor *i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	//  idt_init();
	//  idt_activate();
	//  outb(0x60, 0x10);

	set_mode(320, 200, 8);
	clear_screen_withcolor(0x01);
	color_demo();
}
