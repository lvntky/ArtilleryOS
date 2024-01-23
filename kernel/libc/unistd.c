/**
 * @file unistd.c
 * 
 * MIT License
 *
 * Copyright (c) 2023, Lukas Jackson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "../include/unistd.h"

ssize_t read(int fd, void *buf, size_t count)
{
	if (count == 0)
		return 0;
	if (fd < 0) {
		return -1;
	}
	if (buf == NULL) {
		return -1;
	}

	return -1;
}

ssize_t write(int fd, const void *buf, size_t count)
{
	if (count == 0)
		return 0;
	if (fd < 0) {
		return -1;
	}
	if (buf == NULL) {
		return -1;
	}

	return -1;
}

int close(int fd)
{
	if (fd < 0) {
		return -1;
	}

	return -1;
}

off_t lseek(int fd, off_t offset, int whence)
{
	if (fd < 0) {
		return -1;
	}
	switch (whence) {
	case SEEK_SET:
	case SEEK_CUR:
	case SEEK_END:
		break;
	default:
		return -1;
	}

	return -1;
}

int access(const char *path, int mode)
{
	if (path == NULL || (mode & ~(R_OK | W_OK | X_OK | F_OK)) != 0) {
		return -1;
	}

	return -1;
}

int chdir(const char *path)
{
	if (path == NULL) {
		return -1;
	}

	return -1;
}

char *getcwd(char *buf, size_t size)
{
	return NULL;
}

int unlink(const char *path)
{
	if (path == NULL) {
		return -1;
	}

	return -1;
}

unsigned int alarm(unsigned int seconds)
{
    
    return 0;
}

void sleep(unsigned int seconds)
{
    return seconds;
}
