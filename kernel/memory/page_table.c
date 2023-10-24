#include "include/page_table.h"

uint32_t free_pages;
uint32_t free_page_bitmap[BITMAP_SIZE];

void mark_free(uint32_t page_number);
void mark_unavailable(uint32_t page_number);
uint32_t page_number(uint32_t address);

uint32_t make_page_directory_entry(void *page_table_physical_address,
				   enum page_size_t page_size,
				   bool cache_disabled, bool write_through,
				   enum page_privilege_t privelage,
				   enum page_permissions_t permissions,
				   bool present)
{
	uint32_t entry = (uint32_t)page_table_physical_address;
	entry |= page_size << 7;
	entry |= cache_disabled << 4;
	entry |= write_through << 3;
	entry |= privelage << 2;
	entry |= permissions << 1;
	entry |= present;

	return entry;
}

bool get_present_from_pde(uint32_t pde)
{
	return (pde & 0b1);
}

uint32_t make_page_table_entry(void *page_frame_address, bool global,
			       bool cache_disabled, bool write_through,
			       enum page_privilege_t privelage,
			       enum page_permissions_t permissions,
			       bool present)
{
	uint32_t entry = (uint32_t)page_frame_address;
	entry |= global << 8;
	entry |= cache_disabled << 6;
	entry |= write_through << 3;
	entry |= privelage << 2;
	entry |= permissions << 1;
	entry |= present;

	return entry;
}

bool get_present_from_pte(uint32_t pte)
{
	return (pte & 0b1);
}

void *allocate_physical_page()
{
	for (uint32_t index = 0; index < BITMAP_SIZE; index++) {
		if (free_page_bitmap[index] != 0) {
			for (uint8_t bit = 0; bit < 32; bit++) {
				if ((free_page_bitmap[index] & (1 << bit)) !=
				    0) {
					uint32_t page_number = index * 32 + bit;
					mark_unavailable(page_number);
					void *page_start =
						(void *)(page_number
							 << PAGE_OFFSET_BITS);
					return page_start;
				}
			}
		}
	}

	// Out of physical memory

	panic("Out of physcial memory!",
	      "page_table.c, allocate_physical_page()");

	return NULL;
}

void *page_table_virtual_address(uint16_t page_table_number)
{
	uint32_t virtual_address = 0xFFC00000;

	virtual_address |= (page_table_number << PAGE_OFFSET_BITS);

	return (void *)virtual_address;
}

page_directory_t kernel_page_directory_init()
{
	page_directory_t pd = (page_directory_t)&page_directory_virtual_address;

	uint32_t pde = make_page_directory_entry(
		(void *)&page_directory_physical_address, FOUR_KB, false, false,
		SUPERVISOR, READ_WRITE, true);
	pd[1023] = pde;

	void *page_table_physical_address = allocate_physical_page();
	pd[KERNEL_PAGE_TABLE_NUMBER] = make_page_directory_entry(
		page_table_physical_address, FOUR_KB, false, false, SUPERVISOR,
		READ_WRITE, true);

	page_table_t pt = (page_table_t)page_table_virtual_address(
		KERNEL_PAGE_TABLE_NUMBER);
	for (uint16_t i = 0; i < 1024; i++) {
		void *page_physical_address = (void *)(i * PAGE_SIZE_BYTES);
		pt[i] = make_page_table_entry(page_physical_address, false,
					      false, false, SUPERVISOR,
					      READ_WRITE, true);
	}

	return pd;
}

uint32_t num_present_pages(page_directory_t pd)
{
	uint32_t num = 0;
	for (int i = 0; i < 1024; i++) {
		uint32_t entry = pd[i];
		bool present = entry & 0x1;

		if (present) {
			num += 1;
		}
	}
	return num;
}

uint32_t round_up_to_nearest_page_start(uint32_t address)
{
	if ((address & 0xFFFFF000) != address) {
		address &= 0xFFFFF000;
		address += 0x00001000;
	}

	return address;
}

uint32_t round_down_to_nearest_page_start(uint32_t address)
{
	return address & 0xFFFFF000;
}

uint32_t page_number(uint32_t address)
{
	return address >> PAGE_OFFSET_BITS;
}

void mark_free(uint32_t page_number)
{
	uint32_t index = page_number >> 5;
	uint32_t bit = page_number & 0b11111;
	uint32_t value = free_page_bitmap[index];

	if ((value & (1 << bit)) == 0) {
		// Page was not free before. Update statistics.
		free_pages++;
	}

	value |= (1 << bit);
	free_page_bitmap[index] = value;
}

void mark_unavailable(uint32_t physical_page_number)
{
	uint32_t index = physical_page_number >> 5;
	uint32_t bit = physical_page_number & 0b11111;

	uint32_t value = free_page_bitmap[index];

	if ((value & (1 << bit)) == 1) {
		free_pages--;
	}

	value &= ~(1 << bit);
	free_page_bitmap[index] = value;
}