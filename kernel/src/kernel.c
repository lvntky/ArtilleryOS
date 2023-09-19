#include <kernel.h>
#include <tty.h>
#include "../libc/stdio.h"
#include <gdt.h>
#include <ll_io.h>

void kernel_main(void)
{
	terminal_init();
	init_gdt();
	printf("\n\n    ===========================================\n");
	printf("    TODO FOR NEXT RELEASE:\n");
	printf("    - [ ] IDT\n");
	printf("    - [ ] Keyboard\n");
	printf("    - [ ] Mause\n");
	printf("    ===========================================\n");
}