#include "./include/vga_driver.h"

unsigned int vga_mode = 0;

unsigned int get_graphics_reg(unsigned int index)
{
	unsigned int saved_addr_reg = insb(GRAPHICS_REG_ADDR);
	outb(GRAPHICS_REG_ADDR, index);
	unsigned int graphics_reg_value = insb(GRAPHICS_REG_DATA);
	outb(GRAPHICS_REG_ADDR,
	     saved_addr_reg); // restore address register
	return graphics_reg_value;
}

void set_graphics_reg(unsigned int index, unsigned int value)
{
	unsigned int saved_addr_reg = insb(GRAPHICS_REG_ADDR);
	outb(GRAPHICS_REG_ADDR, index);
	outb(GRAPHICS_REG_DATA, value);
	outb(GRAPHICS_REG_ADDR,
	     saved_addr_reg); // restore address register
}
void vga_enter()
{
	if (vga_mode == 1)
		return;
	vga_mode = 1;
	printf("Attempting to switch modes...");
	for (int i = 500; i > 0; i--) {
		printf("\n Setting graphics: %d", i / 10);
	}

	// Save video memory somewhere else
	// 0xb8000 to 0xbffff (32K)
	//memcpy(0x0010b8000, 0xb8000, COLS * ROWS * 2);

	// Set alphanumeric disable = 1
	unsigned int misc_reg = get_graphics_reg(GRAPHICS_IDX_MISC);
	misc_reg |= 1; // bit 0 is alphanumeric disable, set it to 1
	set_graphics_reg(GRAPHICS_IDX_MISC, misc_reg);
}
void vga_clear_screen()
{
	// Note: "clear_screen" name conflicted with something in screen.h
	// Now I see why namespacing is a thing
	for (int i = 0; i < 320; i++) {
		for (int j = 0; j < 200; j++) {
			vga_plot_pixel(i, j, COLOR_PURPLE);
		}
	}
}
void vga_plot_pixel(int x, int y, unsigned short color)
{
	unsigned short offset = x + 320 * y;
	unsigned char *VGA = (unsigned char *)VGA_ADDRESS;
	VGA[offset] = color;
}