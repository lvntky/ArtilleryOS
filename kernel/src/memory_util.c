#include "../include/memory_util.h"

void *memcpy(void *dest, const void *src, size_t n)
{
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *)src;

	for (size_t i = 0; i < n; i++) {
		dest_ptr[i] = src_ptr[i];
	}

	return dest;
}

// TODO: check if its thread safe
void *memset(void *src, int c, size_t n)
{
	char *src_ptr = (char *)src;
	for (size_t i = 0; i < n; i++) {
		src_ptr[i] = (char)c;
	}

	return src;
}
