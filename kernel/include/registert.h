#ifndef _REGISTERT_H_
#define _REGISTERT_H_

typedef struct register_t {
	unsigned int gs, fs, es, ds; /* pushed the segs last */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx,
		eax; /* pushed by 'pusha' */
	unsigned int int_no,
		err_code; /* our 'push byte #' and ecodes do this */
	unsigned int eip, cs, eflags, useresp,
		ss; /* pushed by the processor automatically */
} register_t;

#endif