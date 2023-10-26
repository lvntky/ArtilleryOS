#include "../include/kernel.h"

void kernel_main(multiboot_info_t *mboot_info, unsigned int magic)
{
	terminal_init();
	get_cpu_info();
	qemu_init_debug();
	gdt_init();
	idt_init();
	timer_init(50);
	keyboard_init();
	printf("Cheking multiboot magic...\n");
	printf("Magic: 0x%x\n", magic);

	if (mboot_info->flags & 0x1) {
		printf("=== Memory Information ===\n");
		printf("Lower Memory: 0x%x\n", mboot_info->mem_lower);
		printf("Upper Memory: 0x%x\n", mboot_info->mem_upper);
	} else {
		panic("Can't get memory information",
		      "loader.asm, multiboot.h");
	}

	// set_mode(320, 200, 8);
	// clear_screen_withcolor(0x04);
}
