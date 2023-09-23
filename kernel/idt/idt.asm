section .asm

global error
global idt_load
; Can be done in inline assembly
idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]
    pop ebp
    ret
error:
    int 0
