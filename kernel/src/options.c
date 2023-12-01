/**
 * @file options.c
 * @author levent kaya
 * @brief optional and configurable inits
 * @version 0.1
 * @date 2023-11-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/options.h"
#include "../include/kernel.h"

void optional_inits()
{
#if TEMPFS_INFO

	// list the contents of /
	int i = 0;
	struct dirent *node = 0;
	while ((node = readdir_fs(fs_root, i)) != 0) {
		tempfs_node_t *fsnode = finddir_fs(fs_root, node->name);

		if ((fsnode->flags & 0x7) == FS_DIRECTORY) {
			printf("\n\t>Directory: %s\n", node->name);
		} else {
			printf("\t\t>File: %s\n", node->name);
			qemu_write_string("File: %s\n", node->name);
			printf("\t\t\t>content: {\n\t\t\t\t");
			unsigned char buf[256];
			uint32_t sz = read_fs(fsnode, 0, 256, buf);
			int j;

			for (j = 0; j < sz; j++) {
				printf("%c", buf[j]);
			}

			printf("\t\t\t}\n");
		}
		i++;
	}
#endif

#if DISPLAY_VBE_INFO
	display_vbe_info(mbinfo);
#endif

// test random
#if TEST_RANDOM
	srand(42);
	int random = rand(5, 1452);
	qemu_write_string("%d", random);
#endif

#if TEST_IDT
	__asm__ __volatile("int $0x0");
#endif

#if GUI_MODE
	set_mode(320, 200, 8);
	clear_screen_withcolor(0x3F);

#if VGA_DEMO
	int color = 0;
	while (1) {
		if (color > 256) {
			color = 0;
		}
		for (int i = 0; i < 99999999; i++) {
			// pseudo sleep()
		}
		gui_draw_string(8, 32, " > VGA Demo!", color);
		for (int i = 0; i < 99999999; i++) {
			// pseudo sleep()
		}
		color++;
	}

#endif

#endif
}
