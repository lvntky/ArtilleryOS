#include "../include/multiboot_module.h"

uint32_t end_address_of_modules(multiboot_info_t *mbinfo)
{
	uint32_t modules_end = 0;

	multiboot_module_t *module = (multiboot_module_t *)mbinfo->mods_addr;
	for (uint32_t i = 0; i < mbinfo->mods_count; ++i, ++module) {
		if (module->mod_end) {
			modules_end = module->mod_end;
		}
	}
	return modules_end;
}

uint32_t total_sizeof_modules(multiboot_info_t *mbifo)
{
	uint32_t size = 0;

	multiboot_module_t *module = (multiboot_module_t *)mbifo->mods_addr;
	for (uint32_t i = 0; i < mbifo->mods_count; ++i, ++module) {
		size += (module->mod_end - module->mod_start);
	}

	return size;
}

void copy_modules(multiboot_info_t *mbinfo, uint32_t dest)
{
	uint32_t size = 0;
	multiboot_module_t *module = (multiboot_module_t *)mbinfo->mods_addr;
	for (uint32_t i = 0; i < mbinfo->mods_count; ++i, ++module) {
		size = module->mod_end - module->mod_start;
		memcpy((void *)dest, (void *)module->mod_start, size);

		module->mod_start = dest;
		module->mod_end = dest + size;

		dest += size;
	}
}

void move_multiboot_modules(multiboot_info_t *mbinfo)
{
	uint32_t end_addr, start_addr, total_size;
	if (ARE_MODULES_ENABLED(mbinfo->flags)) {
		start_addr = mbinfo->mods_addr;
		end_addr = end_address_of_modules(mbinfo);
		total_size = total_sizeof_modules(mbinfo);

		if (end_addr < MODULES_BASE_PHYSICAL_ADDRESS) {
			copy_modules(mbinfo, MODULES_BASE_VIRTUAL_ADDRESS);
		} else if (start_addr >
			   (MODULES_BASE_PHYSICAL_ADDRESS + total_size)) {
			copy_modules(mbinfo, MODULES_BASE_VIRTUAL_ADDRESS);
		} else {
			uint32_t tmp_area = 0;
			if (end_addr <
			    MODULES_BASE_PHYSICAL_ADDRESS + total_size) {
				tmp_area = NEXT_ADDR(
					MODULES_BASE_PHYSICAL_ADDRESS +
					total_size);
			} else {
				tmp_area = NEXT_ADDR(end_addr);
			}

			copy_modules(mbinfo, tmp_area);
			copy_modules(mbinfo, MODULES_BASE_VIRTUAL_ADDRESS);
		}
	}
}