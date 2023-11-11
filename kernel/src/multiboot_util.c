#include "../include/multiboot_util.h"

multiboot_info_t *remap_multiboot_info(uint32_t mbinfo_addr)
{
	multiboot_info_t *mbinfo =
		(multiboot_info_t *)(mbinfo_addr + KERNEL_BASE_ADDR);

	mbinfo->mmap_addr += KERNEL_BASE_ADDR;

	return mbinfo;
}

void display_memory_info(multiboot_info_t *mbinfo,
			 kernel_mem_limits_t *kmlimits)
{
	qemu_write_string("\n%s %s START\n", DEBUG_OUTPUT, MEMORY_OUTPUT);
	/* From the GRUB multiboot manual section 3.3 boot information format
     * If flags[0] is set, then the fields mem_lower and mem_upper can be 
     * accessed.
     * If flags[6] is set, then the fields mmap_length and mmap_addr can be
     * accessed, which contains a complete memory map. 
	 */
	if (mbinfo->flags & 0x00000001) {
		qemu_write_string("%s Size of the lower memory: %d kB\n",
				  INFORMATION_OUTPUT, mbinfo->mem_lower);
		qemu_write_string("%s Size of the upper memory: %d kB\n",
				  INFORMATION_OUTPUT, mbinfo->mem_upper);
	}

	if (mbinfo->flags & 0x00000020) {
		multiboot_memory_map_t *entry =
			(multiboot_memory_map_t *)mbinfo->mmap_addr;
		while ((uint32_t)entry <
		       mbinfo->mmap_addr + mbinfo->mmap_length) {
			if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
				qemu_write_string("%s Avaliable memory: ",
						  INFORMATION_OUTPUT);
			} else {
				qemu_write_string("%s Reserved memory: ",
						  INFORMATION_OUTPUT);
			}
			/*
			* FIX: lld needed, %d overflows
			*/
			qemu_write_string("address: %d", (uint32_t)entry->addr);
			qemu_write_string(", length: %d\n",
					  (uint32_t)entry->len);

			entry = (multiboot_memory_map_t *)(((uint32_t)entry) +
							   entry->size +
							   sizeof(entry->size));
		}
	}
	qemu_write_string("%s Kernel physical start: 0x%x\n",
			  INFORMATION_OUTPUT, kmlimits->kernel_physical_start);
	qemu_write_string("%s Kernel physical end: 0x%x\n", INFORMATION_OUTPUT,
			  kmlimits->kernel_physical_end);
	qemu_write_string("%s Kernel virtual start: 0x%x\n", INFORMATION_OUTPUT,
			  kmlimits->kernel_virtual_start);
	qemu_write_string("%s Kernel virtual end: 0x%x\n", INFORMATION_OUTPUT,
			  kmlimits->kernel_virtual_end);

	qemu_write_string("%s %s END\n\n", DEBUG_OUTPUT, MEMORY_OUTPUT);
}

void check_mboot_bootloader_magic(uint32_t magic)
{
	qemu_write_string("%s Checking multiboot header magic...\n",
			  INFORMATION_OUTPUT);
	if (magic == MULTIBOOT_BOOTLOADER_MAGIC) {
		qemu_write_string(
			"%s Multiboot header magic is correct: 0x%x\n",
			POSITIVE_OUTPUT, magic);
	} else {
		qemu_write_string(
			"%s Multiboot header magic is invalid: 0x%x\n",
			NEGATIVE_OUTPUT, magic);
		panic("Invalid multiboot magic",
		      "loader.asm - multiboot_util.c");
	}
}