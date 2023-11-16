#ifndef _COMMON_H_
#define _COMMON_H_

#define UNUSED_ARGUMENT(x) (void)x; //small hack for gcc :^)
#define KERNEL_BASE_ADDR 0xC0000000

#define VIRTUAL_TO_PHYSICAL(addr) ((addr)-KERNEL_BASE_ADDR)
#define PHYSICAL_TO_VIRTUAL(addr) ((addr) + KERNEL_BASE_ADDR)

#define KERNEL_HEAP_SIZE 0x10000

#define NEXT_ADDR(addr) (addr) + (4 - ((addr) % 4))

#endif