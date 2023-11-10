#include "../include/multiboot_util.h"

void display_memory_info(multiboot_info_t *mbinfo)
{
	qemu_write_string("\n%s INFO DUMP %s\n", MEMORY_OUTPUT, MEMORY_OUTPUT);
	/* From the GRUB multiboot manual section 3.3 boot information format
     * If flags[0] is set, then the fields mem_lower and mem_upper can be 
     * accessed.
     * If flags[6] is set, then the fields mmap_length and mmap_addr can be
     * accessed, which contains a complete memory map. 
	 */
	if (mbinfo->flags & 0x00000001) {
		qemu_write_string("%s Size of the lower memory: %d kB\n",
				  INFORMATION_OUTPUT, mbinfo->mem_lower);
		qemu_write_string("%s Size of the upper memory: %d kB\n\n",
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
}