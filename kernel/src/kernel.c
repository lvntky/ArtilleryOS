#include "./kernel.h"
#include "./tty.h"
#include "./idt.h"
#include "./ll_io.h"

void kernel_main()
{
	terminal_init();
	idt_init();
	outb(0x60, 0xff);
}
