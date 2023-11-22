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

void reverse_dbg(char *str, int len)
{
	int start = 0;
	int end = (len - 1);
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
void itoa_dbg(unsigned int num, char *buffer, int base)
{
	int i = 0;

	if (num == 0) {
		buffer[i++] = '0';
		buffer[i] = '\0';
		return;
	}

	while (num != 0) {
		int remainder = num % base;
		buffer[i++] = (remainder < 10) ? (remainder + '0') :
						 (remainder - 10 + 'A');
		num = num / base;
	}

	buffer[i] = '\0';

	reverse_dbg(buffer, i);
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

void qemu_print_register(register_t *reg)
{
	qemu_write_string("%s Registers dump:\n", REGISTER_OUTPUT);

	qemu_write_string("%s eax: 0x%x ebx: 0x%x ecx: 0x%x edx: 0x%x\n",
			  REGISTER_OUTPUT, reg->eax, reg->ebx, reg->ecx,
			  reg->edx);

	qemu_write_string("%s edi: 0x%x esi: 0x%x ebp: 0x%x esp: 0x%x\n",
			  REGISTER_OUTPUT, reg->edi, reg->esi, reg->ebp,
			  reg->esp);

	qemu_write_string(
		"%s eip: 0x%x cs: 0x%x ss: 0x%x eflags: 0x%x useresp: 0x%x\n",
		REGISTER_OUTPUT, reg->eip, reg->ss, reg->eflags, reg->useresp);
}