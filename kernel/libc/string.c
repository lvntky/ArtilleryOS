#include "./include/string.h"

void *memset(void *ptr, int value, size_t num)
{
	unsigned char *p = ptr;
	unsigned char val = (unsigned char)value;

	for (size_t i = 0; i < num; i++) {
		p[i] = val;
	}

	return ptr;
}

void *memcpy(void *destination, const void *source, size_t num_bytes)
{
	// Cast void pointers to char pointers for byte-wise copying
	char *dest_ptr = (char *)destination;
	const char *src_ptr = (const char *)source;

	// Copy each byte from source to destination
	for (size_t i = 0; i < num_bytes; ++i) {
		dest_ptr[i] = src_ptr[i];
	}

	return destination;
}

int strcmp(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
		str1++;
		str2++;
	}

	if (*str1 == *str2) {
		return 0; // Strings are equal
	} else if (*str1 < *str2) {
		return -1; // First differing character in str1 is smaller
	} else {
		return 1; // First differing character in str1 is larger
	}
}

#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;

	// If source and destination overlap and source is before destination
	if (s < d && d < s + n) {
		s += n;
		d += n;
		while (n--) {
			*(--d) = *(--s);
		}
	} else {
		while (n--) {
			*d++ = *s++;
		}
	}

	return dest;
}
