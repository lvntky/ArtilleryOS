#include "./include/vga_driver.h"

// Function to write registers
void write_registers(uint8_t *registers)
{
	// MISC
	outb(MISC_PORT, *(registers++));

	// Sequencer
	for (uint8_t i = 0; i < 5; i++) {
		outb(SEQUENCER_INDEX_PORT, i);
		outb(SEQUENCER_DATA_PORT, *(registers++));
	}

	// Cathode Ray Tube Controller
	outb(CRT_CONTROLLER_INDEX_PORT, 0x03);
	outb(CRT_CONTROLLER_DATA_PORT, insb(CRT_CONTROLLER_DATA_PORT) | 0x80);
	outb(CRT_CONTROLLER_INDEX_PORT, 0x11);
	outb(CRT_CONTROLLER_DATA_PORT, insb(CRT_CONTROLLER_DATA_PORT) & ~0x80);

	registers[0x03] = registers[0x03] | 0x80;
	registers[0x11] = registers[0x11] & ~0x80;

	for (uint8_t i = 0; i < 25; i++) {
		outb(CRT_CONTROLLER_INDEX_PORT, i);
		outb(CRT_CONTROLLER_DATA_PORT, *(registers++));
	}

	// Graphics Controller
	for (uint8_t i = 0; i < 9; i++) {
		outb(GRAPHICS_CONTROLLER_INDEX_PORT, i);
		outb(GRAPHICS_CONTROLLER_DATA_PORT, *(registers++));
	}

	// Attribute Controller
	for (uint8_t i = 0; i < 21; i++) {
		insb(ATTRIBUTE_CONTROLLER_RESET_PORT);
		outb(ATTRIBUTE_CONTROLLER_INDEX_PORT, i);
		outb(ATTRIBUTE_CONTROLLER_WRITE_PORT, *(registers++));
	}

	insb(ATTRIBUTE_CONTROLLER_RESET_PORT);
	outb(ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}

// Function to check if VGA mode is supported
int supports_mode(uint32_t width, uint32_t height, uint32_t colordepth)
{
	return width == VGA_GFX_WIDTH && height == VGA_GFX_HEIGHT &&
	       colordepth == VGA_GFX_COLOR_DEPTH;
}

// Function to set VGA mode
int set_mode(uint32_t width, uint32_t height, uint32_t colordepth)
{
	if (!supports_mode(width, height, colordepth))
		return 0;

	unsigned char g_320x200x256[] = {
		/* MISC */
		0x63,
		/* SEQ */
		0x03, 0x01, 0x0F, 0x00, 0x0E,
		/* CRT */
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x0E, 0x8F, 0x28,
		0x40, 0x96, 0xB9, 0xA3, 0xFF,
		/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
		/* AC */
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00
	};

	write_registers(g_320x200x256);
	return 1;
}

// Function to get frame buffer segment
uint8_t *get_frame_buffer_segment()
{
	outb(GRAPHICS_CONTROLLER_INDEX_PORT, 0x06);
	uint8_t segmentNumber = insb(GRAPHICS_CONTROLLER_DATA_PORT) & (3 << 2);
	switch (segmentNumber) {
	default:
	case 0 << 2:
		return (uint8_t *)0x00000;
	case 1 << 2:
		return (uint8_t *)0xA0000;
	case 2 << 2:
		return (uint8_t *)0xB0000;
	case 3 << 2:
		return (uint8_t *)0xB8000;
	}
}

// Function to put a pixel on the screen
void put_pixel(uint32_t x, uint32_t y, uint8_t colorIndex)
{
	uint8_t *pixelAddress =
		get_frame_buffer_segment() + VGA_GFX_WIDTH * y + x;
	*pixelAddress = colorIndex;
}

// Function to get the color index
uint8_t get_color_index(uint8_t r, uint8_t g, uint8_t b)
{
	if (r == 0x00 && g == 0x00 && b == 0xA8)
		return 0x01;
	return 0x02;
}

// Function to put a pixel with RGB color
void put_pixel_rgb(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
	put_pixel(x, y, get_color_index(r, g, b));
}

void clear_screen()
{
	for (int32_t y = 0; y < 200; y++) {
		for (int32_t x = 0; x < 320; x++) {
			put_pixel(x, y, 0x3F);
		}
	}
}

void clear_screen_withcolor(uint8_t color)
{
	for (int32_t y = 0; y < 200; y++) {
		for (int32_t x = 0; x < 320; x++) {
			put_pixel(x, y, color);
		}
	}
}

uint8_t vga_colors[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
			 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F };

void color_demo()
{
	int i = 0;
	while (1) {
		clear_screen_withcolor(i);
		if (i > 16) {
			i = i % 16;
		}
		for (size_t i = 0; i < 99999900; i++) {
			/* code */
		}

		i++;
	}
}