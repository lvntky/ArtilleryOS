#include "../include/kernel.h"

void kernel_main()
{
	terminal_init();
	get_cpu_info();
	gdt_init();
	idt_init();

	set_mode(320, 200, 8);
	clear_screen_withcolor(0x3F);

	int color_i = 0;
	while (1) {
		gui_draw_string(10, 10, "Artillery OS v0.2.3-alpha", color_i);
		for (int i = 0; i < 99999999; i++) {
			/* code */
		}
		gui_draw_string(10, 26, "Enjoy the GUI :^)", 0x00);
		color_i++;
		if (color_i > 16) {
			color_i = 0;
		}
	}

	//color_demo();
}
