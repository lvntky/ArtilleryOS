#include "./include/stdio.h"

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

void itoa(unsigned int num, char *buffer, int base)
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
	reverse(buffer, i);
}

void ftoa(double num, char *buffer, int precision)
{
	// Handle negative numbers
	int is_negative = 0;
	if (num < 0) {
		is_negative = 1;
		num = -num;
	}

	// Extract integer and fractional parts
	unsigned int int_part = (unsigned int)num;
	double frac_part = num - int_part;

	// Convert integer part to string
	itoa(int_part, buffer, 10);

	// Append the decimal point
	int len = strlen(buffer);
	buffer[len] = '.';
	len++;

	// Convert fractional part to string with specified precision
	int i;
	for (i = 0; i < precision; ++i) {
		frac_part *= 10;
		buffer[len + i] = '0' + (int)frac_part;
		frac_part -= (int)frac_part;
	}

	buffer[len + i] = '\0';

	// Add the negative sign if necessary
	if (is_negative) {
		memmove(buffer + 1, buffer, len + i + 1);
		buffer[0] = '-';
	}
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
			case 'u': {
				unsigned int num = va_arg(args, unsigned int);
				char buffer[12]; // Enough for a 32-bit unsigned integer
				itoa(num, buffer, 10);
				int i = 0;
				while (buffer[i]) {
					terminal_write_default(buffer[i]);
					written++;
					i++;
				}
				break;
			}
			case 'f': {
				double num = va_arg(args, double);
				char buffer[30]; // Adjust size as needed
				ftoa(num, buffer,
				     6); // 6 is the default precision, adjust as needed
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
			case 'c': {
				char c = va_arg(args, int);
				terminal_write_default(c);
				written++;
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
