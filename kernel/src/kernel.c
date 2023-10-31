#include "../include/kernel.h"

extern void make_err();
void kernel_main()
{
	terminal_init();
	gdt_init();
	idt_init();

	tss_init(5, 0x10, 0);
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	tss_set_stack(0x10, esp);
#if TEST_IDT
	make_err();
#endif
	//timer_init(150);
	//keyboard_init();

	//print_multiboot_magic(magic);

	/*
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
	*/

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x04);
#endif
}
