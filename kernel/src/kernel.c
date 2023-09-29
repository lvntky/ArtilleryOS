#include "../include/kernel.h"

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
	printf("\nGDT INFO:\n");
	printf("\n Code Segment: 0x%x\n", get_code_segment());
	printf("\n Data Segment: 0x%x\n", get_data_segment());
	//idt_init();

	//  idt_activate();
	//  outb(0x60, 0x10);

	//set_mode(320, 200, 8);
	//clear_screen_withcolor(0x01);
	//color_demo();
}
