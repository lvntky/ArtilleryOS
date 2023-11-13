#include "./include/keyboard.h"

// The Keyboard scancode table
unsigned char kbdus[128] = {
	0,    27,  '1', '2', '3',  '4', '5', '6', '7',	'8', /* 9 */
	'9',  '0', '-', '=', '\b', /* Backspace */
	'\t', /* Tab */
	'q',  'w', 'e', 'r', /* 19 */
	't',  'y', 'u', 'i', 'o',  'p', '[', ']', '\n', /* Enter key */
	0, /* 29   - Control */
	'a',  's', 'd', 'f', 'g',  'h', 'j', 'k', 'l',	';', /* 39 */
	'\'', '`', 0, /* Left shift */
	'\\', 'z', 'x', 'c', 'v',  'b', 'n', /* 49 */
	'm',  ',', '.', '/', 0, /* Right shift */
	'*',  0, /* Alt */
	' ', /* Space bar */
	0, /* Caps lock */
	0, /* 59 - F1 key ... > */
	0,    0,   0,	0,   0,	   0,	0,   0,	  0, /* < ... F10 */
	0, /* 69 - Num lock*/
	0, /* Scroll Lock */
	0, /* Home key */
	0, /* Up Arrow */
	0, /* Page Up */
	'-',  0, /* Left Arrow */
	0,    0, /* Right Arrow */
	'+',  0, /* 79 - End key*/
	0, /* Down Arrow */
	0, /* Page Down */
	0, /* Insert Key */
	0, /* Delete Key */
	0,    0,   0,	0, /* F11 Key */
	0, /* F12 Key */
	0, /* All other keys are undefined */
};

// input from keyboard device
unsigned char scan_code;

// Modifier key state
unsigned char shift_pressed = 0;
unsigned char ctrl_pressed = 0;
int gui_x = 0;
int gui_y = 0;

void keyboard_handler(register_t *reg)
{
	// qemu_write_string("%s keyboard_handler()", DEBUG_OUTPUT);
	scan_code = insb(0x60); // Use inb instead of insb
	if (scan_code < 128) {
		char key = kbdus[scan_code];

		// Handle special keys
		if (key == '\n') {
			putchar('\n'); // Handle Enter
		} else if (key == '\b') {
			putchar('\b'); // Handle Backspace
		} else if (key == '\t') {
		} else if (key != 0) {
			// Check for modifier keys
			if (key == '\b') {
				ctrl_pressed = 1;
			} else if (key == '`') {
				shift_pressed = 1;
			} else if (key >= 'A' && key <= 'Z') {
				shift_pressed = 1;
			}

			// Handle other keys based on modifier state
			if (shift_pressed) {
				// Handle Shift key
				// Modify 'key' as needed
				// Example: Convert 'a' to 'A'
				if (key >= 'a' && key <= 'z') {
					key = key - 32;
				}
			}

			if (ctrl_pressed) {
				// Handle Ctrl key
				// Example: Handle Ctrl + C (interrupt)
				if (key == 'c' || key == 'C') {
					// Implement your Ctrl + C action
				}
			}
#if GUI_MODE
			gui_draw_char(gui_x, gui_y, key, 0x04);
#endif

#if !GUI_MODE
			putchar(key);
#endif
		}
	}
}

void keyboard_init()
{
	install_interrupt_handler(1, keyboard_handler);
	qemu_write_string("%s Keyboard driver initialized\n", POSITIVE_OUTPUT);
}