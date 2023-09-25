#include "./include/vga_driver.h"

void write_registers(uint8_t *register_values)
{
	outb(VGA_MISC_PORT, *(register_values++));

	// sequencer
	for (uint8_t i = 0; i < 5; i++) {
		outb(VGA_SEQUENCER_INDEX_PORT, i);
		outb(VGA_SEQUENCER_DATA_PORT, *(register_values++));
	}

	// cathode ray tube controller
	outb(VGA_CRTC_INDEX_PORT, 0x03);
	uint8_t crtc_data_value = insb(VGA_CRTC_DATA_PORT | 0x80);
	outb(VGA_CRTC_DATA_PORT, crtc_data_value);
	outb(VGA_CRTC_INDEX_PORT, 0x11);
	crtc_data_value = insb(VGA_CRTC_DATA_PORT & ~0x80);

	register_values[0x03] = register_values[0x03] | 0x80;
	register_values[0x11] = register_values[0x11] & ~0x80;

	for (uint8_t j = 0; j < 25; j++) {
		outb(VGA_CRTC_INDEX_PORT, j);
		outb(VGA_CRTC_DATA_PORT, *(register_values++));
	}

	// gfx controller
	for (uint8_t k = 0; k < 9; k++) {
		outb(VGA_GFX_CONTROLLER_INDEX_PORT, k);
		outb(VGA_GFX_CONTROLLER_DATA_PORT, *(register_values++));
	}

	// attribute controller
	for (uint8_t l = 0; l < 21; l++) {
		insb(VGA_ATTRIBUTE_CONTROLLER_RESET_PORT);
		outb(VGA_ATTRIBUTE_CONTROLLER_INDEX_PORT, l);
		outb(VGA_ATTRIBUTE_CONTROLLER_WRITE_PORT, *(register_values++));
	}

	insb(VGA_ATTRIBUTE_CONTROLLER_RESET_PORT);
	outb(VGA_ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}

bool is_mode_supported(uint32_t width, uint32_t height, uint32_t color_depth)
{
	return width == 320 && height == 200 && color_depth == 8;
}

bool set_mode(uint32_t width, uint32_t height, uint32_t color_depth)
{
	if (!is_mode_supported(width, height, color_depth)) {
		return false;
	}

	unsigned char gfx_320x200x256[] = {
		/* MISC */
		0x63,
		/* SEQ */
		0x03, 0x01, 0x0F, 0x00, 0x0E,
		/* CRTC */
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 0x0E, 0x8F, 0x28,
		0x40, 0x96, 0xB9, 0xA3, 0xFF,
		/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
		/* AC */
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00
	};

	write_registers(gfx_320x200x256);
	return true;
}

uint8_t *get_frame_bufer_index()
{
	outb(VGA_GFX_CONTROLLER_INDEX_PORT, 0x06);
	uint8_t segment_number = insb(VGA_GFX_CONTROLLER_DATA_PORT & (3 << 2));

	switch (segment_number) {
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

void put_pixel(uint32_t x, uint32_t y, uint8_t color)
{
	uint8_t *frame_buffer_address = get_frame_bufer_index();
	uint8_t *pixel_address = frame_buffer_address + 320 * y + x;
	*pixel_address = color;
}

uint8_t get_color_index(uint8_t r, uint8_t g, uint8_t b)
{
	if (r == 0x00 && g == 0x00 && b == 0xA8) {
		return 0x01;
	}
	return 0x00;
}

void draw(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
{
	put_pixel(x, y, get_color_index(r, g, b));
}