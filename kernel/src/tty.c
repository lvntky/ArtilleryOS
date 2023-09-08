#include "./tty.h"

void terminal_init(void)
{
	volatile char *vid_mem = (volatile char *)(VIDEO_MEM_ADDRESS);
	unsigned int vid_mem_area = VGA_WIDTH * VGA_HEIGHT;

	for (int i = 0; i < vid_mem_area; i++) {
		vid_mem[i] = '#';
		vid_mem[i + 1] = 0;
	}
}