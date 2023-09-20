# ISRs

.global _isr0
.global _isr1

# Divide by zero exception
_isr0:
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

_isr1:
    cli
    pushl $0
    pushl $1
    jmp isr_common_stub

extern _fault_handler

isr_common_stub:
    pushal
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax   # Load the Kernel Data Segment descriptor!
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax   # Push us the stack
    push %eax
    mov $_fault_handler, %eax
    call *%eax       # A special call, preserves the 'eip' register
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
    add $8, %esp     # Cleans up the pushed error code and pushed ISR number
    iret  