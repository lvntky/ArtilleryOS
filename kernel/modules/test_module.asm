[bits 32]
section .text:
align 4
    mov edi, 0xDEADBEEF 
    int 0x00
    ret