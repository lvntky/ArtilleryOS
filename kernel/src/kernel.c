#include "../include/kernel.h"

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

	optional_inits();
	UNUSED_ARGUMENT(module_entry_point);

	uint32_t initrd_module_location = *((uint32_t *)mbinfo->mods_addr);

	fs_root = tempfs_initrd_init(initrd_module_location);
	if (fs_root != NULL) {
		qemu_write_string("%s TempFS initialized\n", POSITIVE_OUTPUT);
	} else {
		qemu_write_string("%s TempFS can't initialized\n",
				  NEGATIVE_OUTPUT);
	}
}
