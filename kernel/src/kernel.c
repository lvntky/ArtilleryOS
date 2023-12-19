#include "../include/system_headers.h"

void kernel_main(void)
{
	// Ensure the bootloader actually understands our base revision (see spec).
	if (LIMINE_BASE_REVISION_SUPPORTED == false) {
		hcf();
	}

	// Ensure we got a framebuffer.
	if (framebuffer_request.response == NULL ||
	    framebuffer_request.response->framebuffer_count < 1) {
		hcf();
	}

	// Fetch the first framebuffer.
	struct limine_framebuffer *framebuffer =
		framebuffer_request.response->framebuffers[0];

	// Note: we assume the framebuffer model is RGB with 32-bit pixels.
	for (size_t i = 0; i < 100; i++) {
		volatile uint32_t *fb_ptr = framebuffer->address;
		fb_ptr[i] = 0x11ff00;
	}

    init_serial_port(0xE9);
	qemu_log_putc('k');
	qemu_log_putc('a');
	qemu_log_putc('y');
	qemu_log_putc('a');

	hcf();
}
