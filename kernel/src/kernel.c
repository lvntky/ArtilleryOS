#include "../include/kernel.h"

void kernel_main(multiboot_info_t *mbi)
{
	terminal_init();
	qemu_init_debug();
	gdt_init();
	idt_init();
	timer_init(50);
	keyboard_init();
	get_cpu_info();

	uint32_t mbi_flags = mbi->flags;
	printf("Multiboot Flags: 0x%x\n", mbi_flags);

	//set_mode(320, 200, 8);
	//clear_screen_withcolor(0x04);
}
