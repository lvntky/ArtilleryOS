#include "../include/interrupt.h"

uint32_t handle_interrupt(uint8_t interrupt, uint32_t esp)
{
	printf("\nINTERRUPT! [%d]", interrupt);

	return esp;
}