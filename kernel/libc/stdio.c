#include "stdio.h"

void reverse(char *str, int len)
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

void itoa(int num, char *buffer, int base)
{
	int i = 0;
	bool isNegative = false;

	if (num == 0) {
		buffer[i++] = '0';
		buffer[i] = '\0';
		return;
	}

	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	while (num != 0) {
		int remainder = num % base;
		buffer[i++] = (remainder < 10) ? (remainder + '0') :
						 (remainder - 10 + 'A');
		num = num / base;
	}

	if (isNegative) {
		buffer[i++] = '-';
	}

	buffer[i] = '\0';

	reverse(buffer, i);
}

int printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int written = 0;

	while (*format) {
		if (*format != '%') {
			terminal_write_default(*format);
			written++;
		} else {
			format++; // Move past the '%'
			switch (*format) {
			case 'd': {
				int num = va_arg(args, int);
				char buffer[12]; // Enough for a 32-bit integer
				itoa(num, buffer, 10);
				int i = 0;
				while (buffer[i]) {
					terminal_write_default(buffer[i]);
					written++;
					i++;
				}
				break;
			}
			case 's': {
				const char *str = va_arg(args, const char *);
				while (*str) {
					terminal_write_default(*str);
					str++;
					written++;
				}
				break;
			}
			case 'x': {
				unsigned int num = va_arg(args, unsigned int);
				char buffer[12]; // Enough for a 32-bit hexadecimal
				itoa(num, buffer, 16);
				int i = 0;
				while (buffer[i]) {
					terminal_write_default(buffer[i]);
					written++;
					i++;
				}
				break;
			}
			case 'p': {
				void *ptr = va_arg(args, void *);
				uintptr_t num = (uintptr_t)ptr;
				char buffer[18]; // Enough for a 64-bit hexadecimal
				itoa(num, buffer, 16);
				int i = 0;
				while (buffer[i]) {
					terminal_write_default(buffer[i]);
					written++;
					i++;
				}
				break;
			}
			default:
				break;
			}
		}
		format++;
	}

	va_end(args);
	return written;
}

void putchar(char c)
{
	terminal_write_default(c);
}