#include "../include/kernel.h"

int make_error()
{
	int a = 5;
	int b = 0;

	return a / b;
}

void trigger_interrupt()
{
	asm volatile("mov $0x20, %al\n" // Set the interrupt number to 0x20
		     "int $0x00\n" // Trigger the interrupt
	);
}
void kernel_main()
{
	terminal_init();
	get_cpu_info();

	gdt_init();
	idt_init();
	make_error();
	printf("this comes after error");
	//  idt_activate();
	//  outb(0x60, 0x10);

	//set_mode(320, 200, 8);
	//clear_screen_withcolor(0x01);
	//color_demo();
}
