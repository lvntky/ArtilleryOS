#include "./idt.h"
#include "./config.h"
#include "tty.h"
#include "memory_util.h"

struct Idt_desc idt_desctriptors[ARTILLERYOS_MAX_INTERRUPT_SIZE];
struct Idtr idtr_descriptor;

extern void idt_load(struct idtr *ptr);

void idt_set(int int_no, void *address)
{
	struct Idt_desc *desc = &idt_desctriptors[int_no];

	desc->offset_1 = (uint32_t)address & 0x000ffff;
	desc->selector = KERNEL_CODE_SELECTOR;
	desc->zero = 0x00;
	desc->type_attribute = 0xEE;
	desc->offset_2 = (uint32_t)address >> 0x10;
}

void idt_zero()
{
	kernel_print("KENREL_INTERRUPT: Divide by zero error!\n",
		     VGA_COLOR_RED);
}

// initialize the idt with null value
void idt_init(void)
{
	memset(idt_desctriptors, 0, sizeof(idt_desctriptors));
	idtr_descriptor.limit = sizeof(idt_desctriptors) - 1;
	idtr_descriptor.base = idt_desctriptors;

	idt_set(0, idt_zero);

	//load the descriptor table
	idt_load(&idtr_descriptor);
}