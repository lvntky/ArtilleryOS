#ifndef _KERNEL_MEM_LIMITS_H_
#define _KERNEL_MEM_LIMITS_H_

#include <stdint.h>

typedef struct kernel_mem_limits {
    uint32_t kernel_physical_start;
    uint32_t kernel_physical_end;
    uint32_t kernel_virtual_start;
    uint32_t kernel_virtual_end;
} __attribute__((packed)) kernel_mem_limits_t;

#endif