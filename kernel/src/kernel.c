#include "../include/kernel.h"
#include "../include/tty.h"
#include "../include/idt.h"

extern void problem();

void kernel_main()
{
	terminal_init();
	idt_init();
}
