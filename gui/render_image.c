#include "render_image.h"

// Function to render an image on the VGA screen
void render_image(uint8_t *image, uint32_t image_width, uint32_t image_height)
{
	// Assuming the VGA screen size is 320x200
	if (image_width > VGA_GFX_WIDTH || image_height > VGA_GFX_HEIGHT) {
		// Image size exceeds screen size
		return;
	}

	// Calculate the starting position to center the image on the screen
	uint32_t start_x = (VGA_GFX_WIDTH - image_width) / 2;
	uint32_t start_y = (VGA_GFX_HEIGHT - image_height) / 2;

	// Render each pixel of the image on the screen
	for (uint32_t y = 0; y < image_height; y++) {
		for (uint32_t x = 0; x < image_width; x++) {
			// Calculate the pixel position on the screen
			uint32_t screen_x = start_x + x;
			uint32_t screen_y = start_y + y;

			// Get the color from the image
			uint8_t color = image[y * image_width + x];

			// Put the pixel on the screen
			put_pixel(screen_x, screen_y, color);
		}
	}
}
