#include "../include/cpu_info.h"

void get_cpu_info()
{
	unsigned int eax, ebx, ecx, edx;

	__cpuid(0, eax, ebx, ecx, edx);
	printf("\n============================\n");
	printf("CPU INFO\n");

	// Print CPU Vendor ID
	printf("\nCPU Vendor ID: ");
	printf("%c%c%c%c", (char)(ebx), (char)(ebx >> 8), (char)(ebx >> 16),
	       (char)(ebx >> 24));
	printf("%c%c%c%c", (char)(edx), (char)(edx >> 8), (char)(edx >> 16),
	       (char)(edx >> 24));
	printf("%c%c%c%c", (char)(ecx), (char)(ecx >> 8), (char)(ecx >> 16),
	       (char)(ecx >> 24));

	__cpuid(1, eax, ebx, ecx, edx);
	printf("\nCPU Family: %d \nModel: %d \nStepping: %d\n",
	       (eax >> 8) & 0xF, (eax >> 4) & 0xF, eax & 0xF);
	printf("============================\n");
}
