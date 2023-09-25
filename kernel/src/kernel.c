#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	idt_init();
	outb(0x60, 0x10);
	

	set_mode(320, 200, 8);
	for (int32_t y = 0; y < 2000; y++)
	{
		for (int32_t x = 0; x < 320; x++)
		{
			put_pixel(x, y, 0x0A);
		}
		
	}
	while (1)
	{
	}
	
}
