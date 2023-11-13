/**
 * @file ext2.h
 * @author levent
 * @brief Artillery OS VFS 1st implementation
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */


// Links:
// https://www.nongnu.org/ext2-doc/
// http://web.mit.edu/tytso/www/linux/ext2intro.html
// https://wiki.osdev.org/Ext2

#ifndef _EXT2_H_
#define _EXT2_H_

#include <stdint.h>


// Needed heap
// Needed ATA driver
// char *device_path 
// char *mount_point
// lotta thing need ffs 
void ext2_init(char * , char *);

#endif