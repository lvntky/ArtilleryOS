#include "../include/kernel.h"
extern void error();
void kernel_main()
{
	terminal_init();
	idt_init();
	error();
}
