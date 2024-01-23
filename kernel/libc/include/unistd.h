/**
 * @file unistd.h
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

#ifndef __UNISTD__H_
#define __UNISTD__H_

#define	R_OK	4		/* Test for read permission.  */
#define	W_OK	2		/* Test for write permission.  */
#define	X_OK	1		/* Test for execute permission.  */
#define	F_OK	0		/* Test for existence.  */

/* Defined types */

/**
 * @brief Represents the size of objects.
 */
typedef unsigned long size_t;

/**
 * @brief Represents the signed size of objects, used for functions returning sizes.
 */
typedef signed long ssize_t;

/**
 * @brief Represents process IDs.
 */
typedef int pid_t;

/**
 * @brief Represents file offsets.
 */
typedef long off_t;

/**
 * @brief Represents microseconds.
 */
typedef unsigned long useconds_t;

/**
 * @brief Represents group IDs.
 */
typedef unsigned int gid_t;

/**
 * @brief Represents user IDs.
 */
typedef unsigned int uid_t;

/* Function prototypes */

/**
 * @brief Reads data from a file descriptor.
 *
 * @param fd File descriptor from which to read.
 * @param buf Buffer to store the read data.
 * @param count Number of bytes to read.
 * @return Returns the number of bytes read, or -1 on error.
 */
extern ssize_t read(int fd, void *buf, size_t count);

/**
 * @brief Writes data to a file descriptor.
 *
 * @param fd File descriptor to which to write.
 * @param buf Buffer containing the data to be written.
 * @param count Number of bytes to write.
 * @return Returns the number of bytes written, or -1 on error.
 */
extern ssize_t write(int fd, const void *buf, size_t count);

/**
 * @brief Closes a file descriptor.
 *
 * @param fd File descriptor to be closed.
 * @return Returns 0 on success, -1 on error.
 */
extern int close(int fd);

/**
 * @brief Moves the file offset associated with a file descriptor.
 *
 * @param fd File descriptor.
 * @param offset Number of bytes to move the file offset.
 * @param whence Reference point for the offset (SEEK_SET, SEEK_CUR, SEEK_END).
 * @return Returns the new file offset, or -1 on error.
 */
extern off_t lseek(int fd, off_t offset, int whence);

/**
 * @brief Checks file access permissions.
 *
 * @param path Path to the file.
 * @param mode Permissions to check (F_OK, R_OK, W_OK, X_OK).
 * @return Returns 0 on success, -1 on error.
 */
extern int access(const char *path, int mode);

/**
 * @brief Changes the current working directory.
 *
 * @param path Path to the directory.
 * @return Returns 0 on success, -1 on error.
 */
extern int chdir(const char *path);

/**
 * @brief Gets the current working directory.
 *
 * @param buf Buffer to store the current working directory.
 * @param size Size of the buffer.
 * @return Returns a pointer to the buffer on success, NULL on error.
 */
extern char *getcwd(char *buf, size_t size);

/**
 * @brief Removes a directory entry.
 *
 * @param path Path to the file to be unlinked.
 * @return Returns 0 on success, -1 on error.
 */
extern int unlink(const char *path);

/**
 * @brief Sets an alarm clock for the delivery of a signal.
 *
 * @param seconds Number of seconds to set the alarm.
 * @return Returns the remaining time on the previous alarm.
 */
extern unsigned int alarm(unsigned int seconds);

/**
 * @brief Suspends execution for a specified number of seconds.
 *
 * @param seconds Number of seconds to sleep.
 */
extern void sleep(unsigned int seconds);

#endif /* __UNISTD__H_ */
