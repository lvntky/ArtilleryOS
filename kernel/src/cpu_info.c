#include "../include/cpu_info.h"

void get_cpu_info()
{
	unsigned int eax, ebx, ecx, edx;

	__cpuid(0, eax, ebx, ecx, edx);
	printf("\n============================\n");
	printf("CPU INFO\n");

	printf("\nCPU Vendor ID: %s", (char *)&ebx, (char *)&edx, (char *)&ecx);

	__cpuid(1, eax, ebx, ecx, edx);
	printf("\nCPU Family: %d \nModel: %d \nStepping: %d\n",
	       (eax >> 8) & 0xF, (eax >> 4) & 0xF, eax & 0xF);
	printf("============================\n");
}