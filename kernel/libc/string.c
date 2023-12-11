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
	} 
	return 	*(unsigned char*)str1 - *(unsigned char*)str2; // return the difference between the
							       // strings
}

#include <stddef.h>

void *memmove(void *destination, const void *source, size_t n)
{
	unsigned char *d = destination;
	const unsigned char *s = source;

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

	return destination;
}

void strcpy(char *destination, char *source)
{
	while (*source != '\0') {
		// Copy the character from source to destination
		*destination = *source;

		// Move to the next character in both source and destination
		destination++;
		source++;
	}

	// Null-terminate the destination string
	*destination = '\0';
}

/**
 *
 * Copies at most n characters from the source string to the destination buffer.
 * If the source string is shorter than n characters, null bytes are added to
 * pad the destination buffer.
 */
void strncpy(char* destination, char* source, size_t n) {
    while (*source != '\0' && n > 0) {
        *destination = *source;
        destination++;
        source++;
        n--;
    }
    while (n > 0) {
        *destination = '\0';
        destination++;
        n--;
    }
}



/**
 *
 * Appends the characters of the source string to the end of the destination
 * string, and null-terminates the resulting string.
 *
 * Returns: A pointer to the destination buffer.
 */
char* strcat(char* destination, char* source) {
    char* retString = destination;

    while (*destination != '\0') {
        destination++;
    }
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return retString;
}



/**
 * Appends at most n characters from the source string to the end of the
 * destination string, and null-terminates the resulting string.
 *
 * Returns: A pointer to the destination buffer.
 */
char* strncat(char* destination, char* source, size_t n) {
    char* retString = destination;

    while (*destination != '\0') {
        destination++;
    }
    while (*source != '\0' && n > 0) {
        *destination = *source;
        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return retString;
}



/**
 *
 * Compares the first n characters of two strings lexicographically.
 *
 * Returns:
 *   -1 if str1 is less than str2,
 *    1 if str1 is greater than str2,
 *    0 if the strings are equal up to n characters.
 */
int strncmp(const char* str1, const char* str2, size_t n) {
    while (*str1 != '\0' && *str2 != '\0' && n > 0) {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        str1++;
        str2++;
        n--;
    }
    if (n > 0) {
        if (*str1 == '\0' && *str2 != '\0') {
            return -1;
        } else if (*str1 != '\0' && *str2 == '\0') {
            return 1;
        }
    }
    return 0;
}



/**
 *
 * Returns a pointer to the first occurrence of 'ch' in the string. If 'ch' is
 * not found, then return NULL.
 */
char* strchr(const char* str, int ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}


/**
 *
 * Returns a pointer to the next token in the string. Modifies the input string
 * by replacing the delimiter after the current token with a null character.
 * On the first call, provide the original string; on subsequent calls, use
 * NULL to continue tokenizing the same string.
 */
char* strtok(char* str, const char* delim) {
    static char* savedToken = NULL;

    if (str != NULL) {
        savedToken = str;
    } else if (savedToken == NULL) {
        return NULL;
    }

    while (*savedToken != '\0' && strchr(delim, *savedToken) != NULL) {
        savedToken++;
    }

    if (*savedToken == '\0') {
        savedToken = NULL;
        return NULL;
    }

    char* tokenStart = savedToken;

    while (*savedToken != '\0' && strchr(delim, *savedToken) == NULL) {
        savedToken++;
    }

    if (*savedToken != '\0') {
        *savedToken = '\0';
        savedToken++;
    }

    return tokenStart;
}

