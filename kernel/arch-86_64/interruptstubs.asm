.set IRQ_BASE, 0x20
.section .text

.extern handle_interrupt

.macro handle_exception num 
.global handle_exception\num\()
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro handle_interrupt_request num 
.global handle_interrupt_request\num\()
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm

handle_interrupt_request 0x00
handle_interrupt_request 0x01

int_bottom:

    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptnumber)
    call handle_interrupt
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

    iret
.data
    interruptnumber: .byte 0