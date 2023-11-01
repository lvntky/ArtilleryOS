#include "../include/kernel.h"

void test_idt()
{
	__asm__("int $0x04");
}

void kernel_main()
{
	terminal_init();
	gdt_init();
	idt_init();
	timer_init(100);
	keyboard_init();

#if TEST_IDT
	test_idt();
#endif

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x04);
#endif
}
