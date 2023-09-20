#include "../include/interrupt.h"

static idt_entry_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
static idt_ptr_t idt_ptr;

void idt_set_descriptor(uint8_t intr_no, void *handler, uint8_t flags)
{
	idt_entry_t *descriptor = &idt[intr_no];

	descriptor->isr_low = (uint32_t)handler & 0xFFFF;
	descriptor->kernel_cs = 0x8; // codesegment in gdt
	descriptor->attributes = flags;
	descriptor->isr_high = ((uint32_t)handler >> 16) & 0xFFFF;
	descriptor->reserved = 0;
}

//extern void isr0();
//extern void isr1();

extern void *isr_stub_table[];

void init_idt()
{
	idt_ptr.base = (uint32_t)&idt[0];
	idt_ptr.limit =
		(uint16_t)(sizeof(idt) * ARTILLERYOS_MAX_INTERRUPT_SIZE) - 1;

	//idt_set_descriptor(0, &isr0, 0x8E);
	//idt_set_descriptor(1, &isr1, 0x8E);
	__asm__ __volatile__("lidt %0" : : "m"(idt_ptr)); // load the new IDT
	__asm__ volatile("sti"); // set the interrupt flag
}

char *exception_messages[32] = { "Division By Zero Exception",
				 "Debug Exception",
				 "Non Maskable Interrupt Exception",
				 "Breakpoint Exception",
				 "Into Detected Overflow Exception" };

void exception_handler(void)
{
	printf("INTERRUPT!\n");
	__asm__ __volatile__("cli; hlt"); // Completely hangs the computer
}