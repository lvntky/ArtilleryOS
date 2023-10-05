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