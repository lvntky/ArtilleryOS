global asm_idt_load
extern idtp

asm_idt_load:
    lidt [idtp]
    ret