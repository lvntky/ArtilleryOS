#ifndef _PAGE_TABLE_H_
#define _PAGE_TABLE_H_

#include <stdint.h>
#include <stdbool.h>
#include "../../include/panic.h"
#include "../../../boot/loader_global_variables.h"

#define PAGE_DIRECTORY_OFFSET_BITS 10
#define PAGE_TABLE_OFFSET_BITS 10
#define PAGE_OFFSET_BITS 12

#define PAGE_SIZE_BYTES 4096
#define PAGE_SIZE_DWORDS 1024

#define KERNEL_PAGE_TABLE_NUMBER 768

#define BITMAP_SIZE 4096

typedef struct kernel_memort_descriptor_t {
	uint32_t kernel_virtual_start;
	uint32_t kernel_virtual_end;
	uint32_t kernel_physical_start;
	uint32_t kernel_physical_end;
} __attribute__((packed)) kernel_memort_descriptor_t;

typedef uint32_t *page_directory_t;
typedef uint32_t *page_table_t;

enum page_permissions_t { READ_ONLY, READ_WRITE };
enum page_privilege_t { SUPERVISOR, USER };
enum page_size_t { FOUR_KB, FOUR_MB };

void map_kernel_into_page_directory(page_directory_t);
page_directory_t kernel_page_directory_init();
uint32_t page_allocator_init(struct kernel_memort_descriptor_t //,
			     //multiboot_info_t* mbinfo
);

uint32_t make_page_directory_entry(void *, enum page_size_t, bool, bool,
				   enum page_privilege_t,
				   enum page_permissions_t, bool);

uint32_t make_page_table_entry(void *, bool, bool, bool, enum page_privilege_t,
			       enum page_permissions_t, bool);

uint32_t num_present_pages(page_directory_t);
uint32_t page_directory_offset(const void *);
void page_in(const void *);
uint32_t page_table_offset(const void *);
//void  print_page_table(FILE file, const uint32_t*);
void *virtual_to_physical(const void *);

#endif