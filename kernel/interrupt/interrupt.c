#include "interrupt.h"

idt_entry_t idt[ARTILLERYOS_MAX_INTERRUPT_SIZE];
idt_ptr_t idt_ptr;

// Interruptmanager Interrupt stubs for ASM

void handle_exception0x00();
void handle_exception0x01();

void ignore_interrupt();

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector,
			 uint8_t flags)
{
	idt[num].base_low = base & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].kernel_segment_selector = selector;
	idt[num].zero = 0;
	idt[num].flags = flags;
}

void idt_init()
{
	uint16_t code_segment = get_code_segment();

	idt_ptr.limit = (sizeof(idt) * ARTILLERYOS_MAX_INTERRUPT_SIZE) - 1;
	idt_ptr.base = (uint32_t)&idt;

	memset(&idt, 0, (sizeof(idt) * ARTILLERYOS_MAX_INTERRUPT_SIZE) - 1);
	/*
	for (uint8_t i = 0; i < ARTILLERYOS_MAX_INTERRUPT_SIZE; i++) {
		idt_set_gate(i, (uint32_t)ignore_interrupt, code_segment, 0x8E);
	}
	*/

	idt_set_gate(0x20, (uint32_t)handle_exception0x00, code_segment, 0x8E);

	//idt_set_gate(0, (uint32_t)im_int_stub_0, 0x08, 0x8E);
	//idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);

	// load idt
	__asm__ __volatile__("lidt %0" : : "m"(idt_ptr));

	// enable interrupts
	__asm__ __volatile__("sti;");
}

// General exception handler
void global_interrupt_handler()
{
	printf("INTERRUPT!\n");
}