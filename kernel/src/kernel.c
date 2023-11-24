#include "../include/kernel.h"

void test_idt()
{
	__asm__("int $0x04");
}

void kernel_main(uint32_t mbaddr, uint32_t mbmagic,
		 kernel_mem_limits_t kmlimits, uint32_t boot_page_directory)
{
	multiboot_info_t *mbinfo = remap_multiboot_info(mbaddr);

	terminal_init();
	gdt_init();
	idt_init();

	// TODO: TSS init need to be fixed
	/*
	tss_init(5, 0x10, 0);
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	tss_set_stack(0x10, esp);
	*/

	timer_init(100);
	keyboard_init();
	check_mboot_bootloader_magic(mbmagic);
	display_memory_info(mbinfo);
	display_kernel_mem_info(&kmlimits);

	paging_init(boot_page_directory);

	kmalloc_init(NEXT_ADDR(kmlimits.kernel_virtual_end), KERNEL_HEAP_SIZE);

	void (*module_entry_point)(void) = (void (*)(void))0xC0400000;
	uint32_t *module = (uint32_t *)0xC0400000;

	for (uint32_t i = 0; i < 4; ++i, ++module) {
		qemu_write_string("m: 0x%x -> 0x%x\n", module, *module);
	}
	//module_entry_point();
	UNUSED_ARGUMENT(module_entry_point);

	// The content reading is still buggy
	// Therefore this is made optional
	// Will fix by the v0.2.5-alpha

#if INIT_VFS
	uint32_t initrd_module_location = *((uint32_t *)mbinfo->mods_addr);

	// TODO:
	// I get the module location with debugging.
	// And this is a bad approach
	// The more valid way to getting this via
	// grub header functions

	fs_root = tempfs_initrd_init(initrd_module_location);

	// list the contents of /
	int i = 0;
	struct dirent *node = 0;
	while ((node = readdir_fs(fs_root, i)) != 0) {
		printf("Found file\n%s", node->name);
		tempfs_node_t *fsnode = finddir_fs(fs_root, node->name);

		if ((fsnode->flags & 0x7) == FS_DIRECTORY) {
			printf("\n    (directory)\n");
		} else {
			printf("\n    contents: \"");
			char buf[256];
			uint32_t sz = read_fs(fsnode, 0, 256, buf);
			int j;
			for (j = 0; j < sz; j++)
				qemu_write_string("%s ", buf[j]);

			printf("\"\n");
		}
		i++;
	}
#endif

#if DISPLAY_VBE_INFO
	display_vbe_info(mbinfo);
#endif

#if TEST_IDT
	test_idt();
#endif

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x3F);

#if VGA_DEMO
	int color = 0;
	while (1) {
		if (color > 256) {
			color = 0;
		}
		for (int i = 0; i < 99999999; i++) {
			// pseudo sleep()
		}
		gui_draw_string(8, 32, " > VGA Demo!", color);
		for (int i = 0; i < 99999999; i++) {
			// pseudo sleep()
		}
		color++;
	}

#endif

#endif
}
