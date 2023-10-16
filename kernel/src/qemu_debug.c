#include "../include/qemu_debug.h"

int init_serial_port(unsigned short port)
{
	outb(port + 1, 0x00); // Disable all interrupts
	outb(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
	outb(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
	outb(port + 1, 0x00); //                  (hi byte)
	outb(port + 3, 0x03); // 8 bits, no parity, one stop bit
	outb(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
	outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
	return 0; // Return success
}

void qemu_init_debug()
{
	if (init_serial_port(QEMU_LOG_SERIAL_PORT) != 0) {
		printf("\n[INIT - ERROR] Cannot initialized the qemu debugger...\n");
	} else {
		printf("[INIT] Qemu debug initialized successfully!\n");
	}
}
void qemu_write_char(char ch)
{
	// Write each character in the prefix individually
	outb(QEMU_LOG_SERIAL_PORT, '[');
	outb(QEMU_LOG_SERIAL_PORT, 'Q');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, 'E');
	outb(QEMU_LOG_SERIAL_PORT, 'M');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, ' ');
	outb(QEMU_LOG_SERIAL_PORT, 'D');
	outb(QEMU_LOG_SERIAL_PORT, 'E');
	outb(QEMU_LOG_SERIAL_PORT, 'B');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, 'G');
	outb(QEMU_LOG_SERIAL_PORT, ']');
	outb(QEMU_LOG_SERIAL_PORT, ' ');

	// Write the actual character
	outb(QEMU_LOG_SERIAL_PORT, ch);
}

void qemu_write_string(char *string)
{
	// Write each character in the prefix individually
	outb(QEMU_LOG_SERIAL_PORT, '[');
	outb(QEMU_LOG_SERIAL_PORT, 'Q');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, 'E');
	outb(QEMU_LOG_SERIAL_PORT, 'M');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, ' ');
	outb(QEMU_LOG_SERIAL_PORT, 'D');
	outb(QEMU_LOG_SERIAL_PORT, 'E');
	outb(QEMU_LOG_SERIAL_PORT, 'B');
	outb(QEMU_LOG_SERIAL_PORT, 'U');
	outb(QEMU_LOG_SERIAL_PORT, 'G');
	outb(QEMU_LOG_SERIAL_PORT, ']');
	outb(QEMU_LOG_SERIAL_PORT, ' ');

	// Write the actual string
	while (*string != '\0') {
		outb(QEMU_LOG_SERIAL_PORT, *string);
		string++;
	}
}