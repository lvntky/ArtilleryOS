#include <kernel.h>
#include <tty.h>
#include "../libc/stdio.h"

void kernel_main(void)
{
	terminal_init();
	printf("\nprintf actually works %s\n", ":^)");
}