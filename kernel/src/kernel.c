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
	uint32_t mbi_lower = mbi->mem_lower;
	uint32_t mbi_upper = mbi->mem_upper;

	printf("flags: 0x%x\n", mbi_flags);
	printf("lower memory: %u kb\n",
	       mbi_lower); // Use %u for unsigned integers
	printf("upper memory: %u kb\n",
	       mbi_upper); // Use %u for unsigned integers

	printf("mmap_length: %u\n", mbi->mmap_length);
	printf("mmap_addr: %u\n", mbi->mmap_addr);

	// set_mode(320, 200, 8);
	// clear_screen_withcolor(0x04);
}
