#include "render_font.h"
#include "font.h"

void draw_char(uint32_t x, uint32_t y, char ch, uint8_t colorIndex)
{
	// Get the bitmap for the character
	char *bitmap = font8x8_basic[(int)ch];

	// Draw each pixel of the character
	for (uint32_t row = 0; row < 8; ++row) {
		for (uint32_t col = 0; col < 8; ++col) {
			if ((bitmap[row] >> col) & 1) {
				// If the bit is set, draw a pixel with the specified color
				put_pixel(x + col, y + row, colorIndex);
			}
		}
	}
}

void gui_draw_string(uint32_t x, uint32_t y, const char *str,
		     uint8_t colorIndex)
{
	// Draw each character in the string
	while (*str != '\0') {
		draw_char(x, y, *str, colorIndex);
		x += 8;
		++str;
	}
}
