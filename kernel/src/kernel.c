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

	print_multiboot_magic(magic);

	if (is_multiboot_info_present(mboot_info)) {
		printf("=== Memory Information ===\n");
		printf("Lower Memory: 0x%x\n", mboot_info->mem_lower);
		printf("Upper Memory: 0x%x\n", mboot_info->mem_upper);

		//uint32_t start_addr = mboot_info->mmap_addr;
		//multiboot_memory_map_t *mmap =
		//	(multiboot_memory_map_t *)start_addr;

	} else {
		panic("Can't get memory information",
		      "loader.asm, multiboot.h");
	}

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x04);
#endif
}
