.set IRQ_BASE, 0x20
.section .text

.extern global_interrupt_handler

.macro handle_exception num
.global handle_exception\num
handle_exception\num:
    movb $\num, (interrupt_number)
    jmp int_bottom
.endm

handle_exception 0x00
handle_exception 0x01

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interrupt_number)
    call global_interrupt_handler
    add %esp, 6
    mov %eax, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

.global ignore_interrupt
ignore_interrupt:
    iret


.data
    interrupt_number: .byte 0