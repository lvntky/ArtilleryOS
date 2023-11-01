global interrupt0
global interrupt1
global interrupt2
global interrupt3
global interrupt4
global interrupt5
global interrupt6
global interrupt7
global interrupt8
global interrupt9
global interrupt10
global interrupt11
global interrupt12
global interrupt13
global interrupt14
global interrupt15

interrupt0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub

; 33: IRQ1
interrupt1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub

; 34: IRQ2
interrupt2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub

; 35: IRQ3
interrupt3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub

; 36: IRQ4
interrupt4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub

; 37: IRQ5
interrupt5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub

; 38: IRQ6
interrupt6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub

; 39: IRQ7
interrupt7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub

; 40: IRQ8
interrupt8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub

; 41: IRQ9
interrupt9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub

; 42: IRQ10
interrupt10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub

; 43: IRQ11
interrupt11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub

; 44: IRQ12
interrupt12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub

; 45: IRQ13
interrupt13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub

; 46: IRQ14
interrupt14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub

; 47: IRQ15
interrupt15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern interrupt_handler

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, interrupt_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret