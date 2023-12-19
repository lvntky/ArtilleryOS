#include "../include/qemu_log.h"
#include "../include/io_port.h"
#include <stdint.h>
#include <sys/types.h>

void (*limine_print)(const char *buf, size_t size) = NULL;
static const char HEX_REFERANCE_TABLE[] = "0123456789abcdef";

int init_serial_port(uint16_t port)
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

void qemu_log_putc(char c) {
    outb(0xe9, c);
}
