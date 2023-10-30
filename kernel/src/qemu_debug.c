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
void itoa_dbg(int n, char *buffer, int base)
{
	int i = 0;
	int isNegative = 0;

	// Handle 0 explicitly, otherwise empty string is printed
	if (n == 0) {
		buffer[i++] = '0';
		buffer[i] = '\0';
	} else {
		// Handle negative numbers only if the base is 10
		if (n < 0 && base == 10) {
			isNegative = 1;
			n = -n;
		}

		// Process individual digits
		while (n != 0) {
			int rem = n % base;
			buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
			n = n / base;
		}

		// Append negative sign for base 10
		if (isNegative && base == 10) {
			buffer[i++] = '-';
		}

		buffer[i] = '\0'; // Null-terminate the string
	}

	// Reverse the string
	int start = 0;
	int end = i - 1;
	while (start < end) {
		// Swap characters
		char temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;
		start++;
		end--;
	}
}

void qemu_write_string(char *format, ...)
{
	va_list args;
	va_start(args, format);

	char *ptr = format;
	while (*ptr != '\0') {
		if (*ptr == '%') {
			ptr++;
			switch (*ptr) {
			case 'x': {
				unsigned int value = va_arg(args, unsigned int);
				char buffer[20];
				itoa_dbg(value, buffer, 16);
				char *buffer_ptr = buffer;
				while (*buffer_ptr != '\0') {
					outb(QEMU_LOG_SERIAL_PORT, *buffer_ptr);
					buffer_ptr++;
				}
				break;
			}
			case 'd': {
				int value = va_arg(args, int);
				char buffer[20];
				itoa_dbg(value, buffer, 10);
				char *buffer_ptr = buffer;
				while (*buffer_ptr != '\0') {
					outb(QEMU_LOG_SERIAL_PORT, *buffer_ptr);
					buffer_ptr++;
				}
				break;
			}
			case 's': {
				char *str = va_arg(args, char *);
				while (*str != '\0') {
					outb(QEMU_LOG_SERIAL_PORT, *str);
					str++;
				}
				break;
			}
			default:
				// Handle unsupported format specifier
				break;
			}
		} else {
			outb(QEMU_LOG_SERIAL_PORT, *ptr);
		}
		ptr++;
	}

	va_end(args);
}
